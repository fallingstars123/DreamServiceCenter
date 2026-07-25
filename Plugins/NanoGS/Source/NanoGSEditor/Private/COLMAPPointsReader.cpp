// Copyright Epic Games, Inc. All Rights Reserved.

#include "COLMAPPointsReader.h"
#include "HAL/PlatformFileManager.h"

namespace
{
	constexpr uint64 MaxReasonablePointCount = 100000000;
	constexpr uint64 MaxReasonableTrackLength = 10000000;
	constexpr float MetersToUE = 100.0f;

	template <typename T>
	bool ReadValue(IFileHandle& File, T& OutValue)
	{
		return File.Read(reinterpret_cast<uint8*>(&OutValue), sizeof(T));
	}

	bool SkipBytes(IFileHandle& File, uint64 NumBytes, int64 FileSize)
	{
		const int64 Current = File.Tell();
		if (NumBytes > static_cast<uint64>(MAX_int64) ||
			Current < 0 ||
			Current > FileSize ||
			NumBytes > static_cast<uint64>(FileSize - Current))
		{
			return false;
		}
		return File.Seek(Current + static_cast<int64>(NumBytes));
	}
}

bool FCOLMAPPointsReader::IsValidPointsFile(const FString& FilePath)
{
	if (!FPaths::GetCleanFilename(FilePath).Equals(TEXT("points3D.bin"), ESearchCase::IgnoreCase))
	{
		return false;
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	TUniquePtr<IFileHandle> File(PlatformFile.OpenRead(*FilePath));
	if (!File || File->Size() < static_cast<int64>(sizeof(uint64)))
	{
		return false;
	}

	uint64 PointCount = 0;
	return ReadValue(*File, PointCount) &&
		PointCount > 0 &&
		PointCount <= MaxReasonablePointCount;
}

bool FCOLMAPPointsReader::ReadPointsFile(
	const FString& FilePath,
	TArray<FGaussianSplatData>& OutSplats,
	FString& OutError)
{
	OutSplats.Reset();
	OutError.Reset();

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	TUniquePtr<IFileHandle> File(PlatformFile.OpenRead(*FilePath));
	if (!File)
	{
		OutError = FString::Printf(TEXT("Could not open COLMAP points file: %s"), *FilePath);
		return false;
	}

	const int64 FileSize = File->Size();
	uint64 PointCount = 0;
	if (!ReadValue(*File, PointCount) || PointCount == 0 || PointCount > MaxReasonablePointCount)
	{
		OutError = TEXT("Invalid COLMAP points3D.bin header or point count.");
		return false;
	}

	if (PointCount > static_cast<uint64>(MAX_int32))
	{
		OutError = TEXT("COLMAP point count exceeds Unreal array limits.");
		return false;
	}

	OutSplats.Reserve(static_cast<int32>(PointCount));

	for (uint64 PointIndex = 0; PointIndex < PointCount; ++PointIndex)
	{
		uint64 PointID = 0;
		double X = 0.0;
		double Y = 0.0;
		double Z = 0.0;
		uint8 R = 0;
		uint8 G = 0;
		uint8 B = 0;
		double Error = 0.0;
		uint64 TrackLength = 0;

		if (!ReadValue(*File, PointID) ||
			!ReadValue(*File, X) ||
			!ReadValue(*File, Y) ||
			!ReadValue(*File, Z) ||
			!ReadValue(*File, R) ||
			!ReadValue(*File, G) ||
			!ReadValue(*File, B) ||
			!ReadValue(*File, Error) ||
			!ReadValue(*File, TrackLength))
		{
			OutError = FString::Printf(TEXT("Unexpected end of file while reading COLMAP point %llu."), PointIndex);
			OutSplats.Reset();
			return false;
		}

		if (TrackLength > MaxReasonableTrackLength ||
			!SkipBytes(*File, TrackLength * sizeof(uint32) * 2, FileSize))
		{
			OutError = FString::Printf(TEXT("Invalid track data for COLMAP point %llu."), PointIndex);
			OutSplats.Reset();
			return false;
		}

		FGaussianSplatData& Splat = OutSplats.AddDefaulted_GetRef();

		// Match the existing PLY import convention:
		// reconstruction Z -> UE X, reconstruction X -> UE Y, -reconstruction Y -> UE Z.
		Splat.Position = FVector3f(
			static_cast<float>(Z * MetersToUE),
			static_cast<float>(X * MetersToUE),
			static_cast<float>(-Y * MetersToUE));

		const FVector3f Color(
			static_cast<float>(R) / 255.0f,
			static_cast<float>(G) / 255.0f,
			static_cast<float>(B) / 255.0f);
		Splat.SH_DC = (Color - FVector3f(0.5f)) / GaussianSplattingConstants::SH_C0;
		Splat.Opacity = 1.0f;
		Splat.Scale = FVector3f::OneVector;
		Splat.Rotation = FQuat4f::Identity;
	}

	if (File->Tell() != FileSize)
	{
		UE_LOG(LogTemp, Verbose, TEXT("COLMAP points3D.bin has %lld trailing bytes"), FileSize - File->Tell());
	}

	return true;
}
