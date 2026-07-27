// Copyright Epic Games, Inc. All Rights Reserved.
// SPZ decoding follows Niantic Labs' MIT-licensed SPZ reference implementation.

#include "SPZFileReader.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "zlib.h"

namespace
{
	constexpr uint32 SPZMagic = 0x5053474e; // "NGSP" in little endian
	constexpr uint8 FlagHasExtensions = 0x2;
	constexpr int32 HeaderSize = 16;
	constexpr int32 MaxSupportedPoints = 100000000;
	constexpr float MetersToUE = 100.0f;
	constexpr float SPZColorScale = 0.15f;
	constexpr float SqrtHalf = 0.7071067811865475f;

#pragma pack(push, 1)
	struct FSPZLegacyHeader
	{
		uint32 Magic;
		uint32 Version;
		uint32 NumPoints;
		uint8 SHDegree;
		uint8 FractionalBits;
		uint8 Flags;
		uint8 Reserved;
	};
#pragma pack(pop)

	static_assert(sizeof(FSPZLegacyHeader) == HeaderSize, "Unexpected SPZ header layout");

	int32 SHCoefficientCount(int32 Degree)
	{
		switch (Degree)
		{
		case 0: return 0;
		case 1: return 3;
		case 2: return 8;
		case 3: return 15;
		default: return -1;
		}
	}

	bool InflateGzip(const TArray<uint8>& Compressed, TArray<uint8>& OutData, FString& OutError)
	{
		if (Compressed.IsEmpty() || Compressed.Num() > static_cast<int64>(MAX_uint32))
		{
			OutError = TEXT("SPZ file is empty or too large for gzip decoding.");
			return false;
		}

		z_stream Stream{};
		Stream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(Compressed.GetData()));
		Stream.avail_in = static_cast<uInt>(Compressed.Num());
		if (inflateInit2(&Stream, 16 + MAX_WBITS) != Z_OK)
		{
			OutError = TEXT("Failed to initialize SPZ gzip decoder.");
			return false;
		}

		constexpr int32 ChunkSize = 1024 * 1024;
		bool bSuccess = false;
		for (;;)
		{
			const int32 OldNum = OutData.Num();
			OutData.AddUninitialized(ChunkSize);
			Stream.next_out = reinterpret_cast<Bytef*>(OutData.GetData() + OldNum);
			Stream.avail_out = ChunkSize;

			const int32 Result = inflate(&Stream, Z_NO_FLUSH);
			const int32 BytesWritten = ChunkSize - static_cast<int32>(Stream.avail_out);
			OutData.SetNum(OldNum + BytesWritten, EAllowShrinking::No);

			if (Result == Z_STREAM_END)
			{
				bSuccess = true;
				break;
			}
			if (Result != Z_OK)
			{
				OutError = FString::Printf(TEXT("Failed to decompress SPZ gzip stream (zlib error %d)."), Result);
				break;
			}
			if (BytesWritten == 0 && Stream.avail_in == 0)
			{
				OutError = TEXT("SPZ gzip stream ended unexpectedly.");
				break;
			}
		}

		inflateEnd(&Stream);
		return bSuccess;
	}

	int32 DecodeSigned24(const uint8* Bytes)
	{
		int32 Value = static_cast<int32>(Bytes[0]) |
			(static_cast<int32>(Bytes[1]) << 8) |
			(static_cast<int32>(Bytes[2]) << 16);
		if ((Value & 0x800000) != 0)
		{
			Value |= static_cast<int32>(0xff000000);
		}
		return Value;
	}

	FQuat4f DecodeQuaternionV2(const uint8* Bytes)
	{
		const float X = static_cast<float>(Bytes[0]) / 127.5f - 1.0f;
		const float Y = static_cast<float>(Bytes[1]) / 127.5f - 1.0f;
		const float Z = static_cast<float>(Bytes[2]) / 127.5f - 1.0f;
		const float W = FMath::Sqrt(FMath::Max(0.0f, 1.0f - X * X - Y * Y - Z * Z));
		return FQuat4f(X, Y, Z, W);
	}

	FQuat4f DecodeQuaternionV3(const uint8* Bytes)
	{
		uint32 Packed = static_cast<uint32>(Bytes[0]) |
			(static_cast<uint32>(Bytes[1]) << 8) |
			(static_cast<uint32>(Bytes[2]) << 16) |
			(static_cast<uint32>(Bytes[3]) << 24);
		const int32 LargestIndex = static_cast<int32>(Packed >> 30);
		float Components[4] = {};
		float SumSquares = 0.0f;
		for (int32 Component = 3; Component >= 0; --Component)
		{
			if (Component == LargestIndex)
			{
				continue;
			}
			const uint32 Magnitude = Packed & 0x1ffu;
			const bool bNegative = ((Packed >> 9) & 1u) != 0;
			Packed >>= 10;
			Components[Component] = SqrtHalf * static_cast<float>(Magnitude) / 511.0f;
			if (bNegative)
			{
				Components[Component] = -Components[Component];
			}
			SumSquares += Components[Component] * Components[Component];
		}
		Components[LargestIndex] = FMath::Sqrt(FMath::Max(0.0f, 1.0f - SumSquares));
		return FQuat4f(Components[0], Components[1], Components[2], Components[3]);
	}

	// RUB -> RDF is a 180-degree X rotation. These signs match Niantic's real-SH ordering.
	constexpr float RUBToRDFSHSigns[15] = {
		-1, -1,  1,
		-1,  1,  1, -1,  1,
		-1,  1, -1, -1,  1, -1,  1
	};
}

bool FSPZFileReader::IsValidSPZFile(const FString& FilePath)
{
	TArray<uint8> Prefix;
	if (!FFileHelper::LoadFileToArray(Prefix, *FilePath) || Prefix.Num() < 2)
	{
		return false;
	}
	return Prefix[0] == 0x1f && Prefix[1] == 0x8b;
}

bool FSPZFileReader::ReadSPZFile(
	const FString& FilePath,
	TArray<FGaussianSplatData>& OutSplats,
	FString& OutError,
	int32* OutSHBands)
{
	OutSplats.Reset();
	OutError.Reset();
	if (OutSHBands)
	{
		*OutSHBands = 0;
	}

	TArray<uint8> Compressed;
	if (!FFileHelper::LoadFileToArray(Compressed, *FilePath))
	{
		OutError = FString::Printf(TEXT("Could not open SPZ file: %s"), *FilePath);
		return false;
	}

	TArray<uint8> Data;
	if (!InflateGzip(Compressed, Data, OutError) || Data.Num() < HeaderSize)
	{
		if (OutError.IsEmpty())
		{
			OutError = TEXT("SPZ decompressed data is too short.");
		}
		return false;
	}

	FSPZLegacyHeader Header{};
	FMemory::Memcpy(&Header, Data.GetData(), sizeof(Header));
	if (Header.Magic != SPZMagic)
	{
		OutError = TEXT("Invalid SPZ magic number.");
		return false;
	}
	if (Header.Version < 2 || Header.Version > 3)
	{
		OutError = FString::Printf(
			TEXT("SPZ version %u is not supported by this importer (supported: legacy gzip versions 2 and 3)."),
			Header.Version);
		return false;
	}
	if (Header.NumPoints == 0 || Header.NumPoints > MaxSupportedPoints)
	{
		OutError = FString::Printf(TEXT("Invalid SPZ point count: %u."), Header.NumPoints);
		return false;
	}
	if ((Header.Flags & FlagHasExtensions) != 0)
	{
		OutError = TEXT("This SPZ contains extensions that may alter coordinates or quantization and cannot be imported safely.");
		return false;
	}

	const int32 SHCount = SHCoefficientCount(Header.SHDegree);
	if (SHCount < 0)
	{
		OutError = FString::Printf(TEXT("Unsupported SPZ SH degree: %u (NanoGS supports up to degree 3)."), Header.SHDegree);
		return false;
	}

	const int64 PointCount = Header.NumPoints;
	const int64 PositionBytes = PointCount * 9;
	const int64 AlphaBytes = PointCount;
	const int64 ColorBytes = PointCount * 3;
	const int64 ScaleBytes = PointCount * 3;
	const int64 RotationStride = Header.Version >= 3 ? 4 : 3;
	const int64 RotationBytes = PointCount * RotationStride;
	const int64 SHBytes = PointCount * SHCount * 3;
	const int64 ExpectedSize = HeaderSize + PositionBytes + AlphaBytes + ColorBytes +
		ScaleBytes + RotationBytes + SHBytes;
	if (ExpectedSize > Data.Num())
	{
		OutError = FString::Printf(
			TEXT("SPZ data is truncated (expected at least %lld bytes, got %d)."),
			ExpectedSize, Data.Num());
		return false;
	}

	const uint8* Positions = Data.GetData() + HeaderSize;
	const uint8* Alphas = Positions + PositionBytes;
	const uint8* Colors = Alphas + AlphaBytes;
	const uint8* Scales = Colors + ColorBytes;
	const uint8* Rotations = Scales + ScaleBytes;
	const uint8* SH = Rotations + RotationBytes;
	const float PositionScale = 1.0f / static_cast<float>(1u << Header.FractionalBits);

	OutSplats.SetNum(static_cast<int32>(PointCount));
	for (int32 Index = 0; Index < static_cast<int32>(PointCount); ++Index)
	{
		FGaussianSplatData& Splat = OutSplats[Index];

		const uint8* Position = Positions + static_cast<int64>(Index) * 9;
		const float RubX = DecodeSigned24(Position + 0) * PositionScale;
		const float RubY = DecodeSigned24(Position + 3) * PositionScale;
		const float RubZ = DecodeSigned24(Position + 6) * PositionScale;

		// SPZ defaults to RUB. Convert RUB -> RDF, then use NanoGS' existing RDF -> UE mapping.
		Splat.Position = FVector3f(-RubZ, RubX, RubY) * MetersToUE;

		const uint8* RotationData = Rotations + static_cast<int64>(Index) * RotationStride;
		const FQuat4f RubRotation = Header.Version >= 3
			? DecodeQuaternionV3(RotationData)
			: DecodeQuaternionV2(RotationData);
		Splat.Rotation = GaussianSplattingUtils::NormalizeQuat(FQuat4f(
			RubRotation.Z, -RubRotation.X, -RubRotation.Y, RubRotation.W));

		const uint8* Scale = Scales + static_cast<int64>(Index) * 3;
		const float ScaleX = FMath::Exp(static_cast<float>(Scale[0]) / 16.0f - 10.0f) * MetersToUE;
		const float ScaleY = FMath::Exp(static_cast<float>(Scale[1]) / 16.0f - 10.0f) * MetersToUE;
		const float ScaleZ = FMath::Exp(static_cast<float>(Scale[2]) / 16.0f - 10.0f) * MetersToUE;
		Splat.Scale = FVector3f(ScaleZ, ScaleX, ScaleY);

		Splat.Opacity = static_cast<float>(Alphas[Index]) / 255.0f;
		const uint8* Color = Colors + static_cast<int64>(Index) * 3;
		Splat.SH_DC = FVector3f(
			(static_cast<float>(Color[0]) / 255.0f - 0.5f) / SPZColorScale,
			(static_cast<float>(Color[1]) / 255.0f - 0.5f) / SPZColorScale,
			(static_cast<float>(Color[2]) / 255.0f - 0.5f) / SPZColorScale);

		const uint8* PointSH = SH + static_cast<int64>(Index) * SHCount * 3;
		for (int32 Coefficient = 0; Coefficient < SHCount; ++Coefficient)
		{
			const float Sign = RUBToRDFSHSigns[Coefficient];
			Splat.SH[Coefficient] = Sign * FVector3f(
				(static_cast<float>(PointSH[Coefficient * 3 + 0]) - 128.0f) / 128.0f,
				(static_cast<float>(PointSH[Coefficient * 3 + 1]) - 128.0f) / 128.0f,
				(static_cast<float>(PointSH[Coefficient * 3 + 2]) - 128.0f) / 128.0f);
		}
	}

	if (OutSHBands)
	{
		*OutSHBands = Header.SHDegree;
	}
	UE_LOG(LogTemp, Log, TEXT("SPZ import: version=%u, splats=%u, SH degree=%u"),
		Header.Version, Header.NumPoints, Header.SHDegree);
	return true;
}
