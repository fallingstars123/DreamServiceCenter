// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoUIMathBackgroundMatte.h"

#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "ImageCore.h"
#include "ImageUtils.h"

namespace AutoUIMathBackgroundMatte_Private
{
	static FORCEINLINE int32 ColorDistSq(const FColor& A, const FColor& B, const bool bIncludeAlpha)
	{
		const int32 Dr = static_cast<int32>(A.R) - static_cast<int32>(B.R);
		const int32 Dg = static_cast<int32>(A.G) - static_cast<int32>(B.G);
		const int32 Db = static_cast<int32>(A.B) - static_cast<int32>(B.B);
		int32 S = Dr * Dr + Dg * Dg + Db * Db;
		if (bIncludeAlpha)
		{
			const int32 Da = static_cast<int32>(A.A) - static_cast<int32>(B.A);
			S += Da * Da;
		}
		return S;
	}

	static bool DecodeSourceToColors(const FImage& Src, UTexture2D* SourceTexture, TArray<FColor>& OutPixels, int32& OutW, int32& OutH, FString& OutError)
	{
		if (!SourceTexture)
		{
			OutError = TEXT("源纹理指针无效。");
			return false;
		}

		OutW = SourceTexture->GetSizeX();
		OutH = SourceTexture->GetSizeY();
		if (OutW <= 0 || OutH <= 0)
		{
			OutError = TEXT("源纹理尺寸无效。");
			return false;
		}

		if (Src.Format != ERawImageFormat::BGRA8)
		{
			OutError = FString::Printf(
				TEXT("当前源像素格式为 %d，数学抠背景仅支持 BGRA8（请在导入/压缩设置中保留可读源或改为 8bit 未压缩源）。"),
				static_cast<int32>(Src.Format));
			return false;
		}

		const int64 N64 = static_cast<int64>(OutW) * static_cast<int64>(OutH);
		const int32 N = static_cast<int32>(N64);
		if (N64 > static_cast<int64>(INT32_MAX) || Src.RawData.Num() < N64 * 4)
		{
			OutError = TEXT("源 RawData 与纹理声明尺寸不匹配或过大。");
			return false;
		}

		OutPixels.SetNumUninitialized(N);
		const uint8* Raw = Src.RawData.GetData();
		for (int32 I = 0; I < N; ++I)
		{
			const uint8* P = Raw + I * 4;
			OutPixels[I] = FColor(P[2], P[1], P[0], P[3]);
		}

		return true;
	}

	static void RemoveSmallForegroundRegions(
		const int32 W,
		const int32 H,
		const FAutoUIMathMatteParams& Params,
		TArray<uint8>& InOutIsBg)
	{
		const int32 MinA = Params.MinForegroundAreaPixels;
		if (MinA <= 1)
		{
			return;
		}

		const int32 N = W * H;
		TArray<uint8> Vis;
		Vis.Init(0, N);

		TArray<int32> Q;
		TArray<int32> Component;
		Q.Reserve(256);
		Component.Reserve(256);

		static constexpr int32 D4xs[] = {1, -1, 0, 0};
		static constexpr int32 D4ys[] = {0, 0, 1, -1};
		static constexpr int32 D8xs[] = {1, -1, 0, 0, 1, 1, -1, -1};
		static constexpr int32 D8ys[] = {0, 0, 1, -1, 1, -1, 1, -1};
		const int32* Dxs = Params.bEightConnected ? D8xs : D4xs;
		const int32* Dys = Params.bEightConnected ? D8ys : D4ys;
		const int32 DCount = Params.bEightConnected ? 8 : 4;

		for (int32 I = 0; I < N; ++I)
		{
			if (InOutIsBg[I] != 0 || Vis[I] != 0)
			{
				continue;
			}

			Q.Reset();
			Component.Reset();
			Q.Add(I);
			Vis[I] = 1;
			Component.Add(I);

			int32 Head = 0;
			while (Head < Q.Num())
			{
				const int32 Cur = Q[Head++];
				const int32 Cy = Cur / W;
				const int32 Cx = Cur - Cy * W;

				for (int32 D = 0; D < DCount; ++D)
				{
					const int32 Nx = Cx + Dxs[D];
					const int32 Ny = Cy + Dys[D];
					if (Nx < 0 || Ny < 0 || Nx >= W || Ny >= H)
					{
						continue;
					}
					const int32 Ni = Ny * W + Nx;
					if (InOutIsBg[Ni] != 0 || Vis[Ni] != 0)
					{
						continue;
					}
					Vis[Ni] = 1;
					Q.Add(Ni);
					Component.Add(Ni);
				}
			}

			if (Component.Num() < MinA)
			{
				for (const int32 Idx : Component)
				{
					InOutIsBg[Idx] = 1;
				}
			}
		}
	}
}

bool AutoUIMathBackgroundMatte::BuildBGRAWithMatte(
	UTexture2D* SourceTexture,
	const FAutoUIMathMatteParams& Params,
	TArray<uint8>& OutBGRA,
	int32& OutWidth,
	int32& OutHeight,
	FString& OutError)
{
	OutBGRA.Reset();
	OutWidth = 0;
	OutHeight = 0;

	if (!SourceTexture)
	{
		OutError = TEXT("未选择纹理。");
		return false;
	}

	FImage SourceImage;
	if (!FImageUtils::GetTexture2DSourceImage(SourceTexture, SourceImage))
	{
		OutError = TEXT("无法读取纹理源像素（可能无源数据或格式不支持）。");
		return false;
	}

	TArray<FColor> Pixels;
	if (!AutoUIMathBackgroundMatte_Private::DecodeSourceToColors(SourceImage, SourceTexture, Pixels, OutWidth, OutHeight, OutError))
	{
		return false;
	}

	const int32 W = OutWidth;
	const int32 H = OutHeight;
	const int64 N64 = static_cast<int64>(W) * static_cast<int64>(H);
	const int32 N = static_cast<int32>(N64);
	const int32 T = FMath::Clamp(Params.ColorTolerance, 1, 255);
	const int32 ThrSq = T * T;
	const bool bIncA = Params.bIncludeAlphaInDistance;

	TArray<uint8> IsBg;
	IsBg.Init(0, N);

	TArray<int32> Queue;
	Queue.Reserve(N);

	auto EnqueueIfNew = [&](const int32 X, const int32 Y)
	{
		if (X < 0 || Y < 0 || X >= W || Y >= H)
		{
			return;
		}
		const int32 Idx = Y * W + X;
		if (IsBg[Idx] != 0)
		{
			return;
		}
		IsBg[Idx] = 1;
		Queue.Add(Idx);
	};

	for (int32 X = 0; X < W; ++X)
	{
		EnqueueIfNew(X, 0);
		EnqueueIfNew(X, H - 1);
	}
	for (int32 Y = 0; Y < H; ++Y)
	{
		EnqueueIfNew(0, Y);
		EnqueueIfNew(W - 1, Y);
	}

	static constexpr int32 D4xs[] = {1, -1, 0, 0};
	static constexpr int32 D4ys[] = {0, 0, 1, -1};
	static constexpr int32 D8xs[] = {1, -1, 0, 0, 1, 1, -1, -1};
	static constexpr int32 D8ys[] = {0, 0, 1, -1, 1, -1, 1, -1};
	const int32* Dxs = Params.bEightConnected ? D8xs : D4xs;
	const int32* Dys = Params.bEightConnected ? D8ys : D4ys;
	const int32 DCount = Params.bEightConnected ? 8 : 4;

	int32 Head = 0;
	while (Head < Queue.Num())
	{
		const int32 Cur = Queue[Head++];
		const int32 Cy = Cur / W;
		const int32 Cx = Cur - Cy * W;
		const FColor& Ccol = Pixels[Cur];

		for (int32 D = 0; D < DCount; ++D)
		{
			const int32 Nx = Cx + Dxs[D];
			const int32 Ny = Cy + Dys[D];
			if (Nx < 0 || Ny < 0 || Nx >= W || Ny >= H)
			{
				continue;
			}
			const int32 Ni = Ny * W + Nx;
			if (IsBg[Ni] != 0)
			{
				continue;
			}
			if (AutoUIMathBackgroundMatte_Private::ColorDistSq(Ccol, Pixels[Ni], bIncA) <= ThrSq)
			{
				IsBg[Ni] = 1;
				Queue.Add(Ni);
			}
		}
	}

	AutoUIMathBackgroundMatte_Private::RemoveSmallForegroundRegions(W, H, Params, IsBg);

	OutBGRA.SetNumUninitialized(N * 4);
	for (int32 I = 0; I < N; ++I)
	{
		const FColor& Src = Pixels[I];
		uint8* Dst = &OutBGRA[I * 4];
		Dst[0] = Src.B;
		Dst[1] = Src.G;
		Dst[2] = Src.R;
		Dst[3] = (IsBg[I] != 0) ? 0 : Src.A;
	}

	return true;
}

bool AutoUIMathBackgroundMatte::UploadBGRAToTransientTexture(
	UTexture2D* DestTexture,
	const int32 Width,
	const int32 Height,
	const TArray<uint8>& BGRA,
	FString& OutError)
{
	if (!DestTexture || Width <= 0 || Height <= 0)
	{
		OutError = TEXT("目标纹理或尺寸无效。");
		return false;
	}

	const int64 Expected = static_cast<int64>(Width) * static_cast<int64>(Height) * 4;
	if (BGRA.Num() < Expected)
	{
		OutError = TEXT("像素缓冲长度不足。");
		return false;
	}

	FTexturePlatformData* PlatformData = DestTexture->GetPlatformData();
	if (!PlatformData || PlatformData->Mips.Num() == 0)
	{
		OutError = TEXT("目标纹理无 Platform Mip 数据。");
		return false;
	}

	FByteBulkData& Bulk = PlatformData->Mips[0].BulkData;
	void* Locked = Bulk.Lock(LOCK_READ_WRITE);
	if (!Locked)
	{
		OutError = TEXT("无法锁定 Mip 写入。");
		return false;
	}

	FMemory::Memcpy(Locked, BGRA.GetData(), static_cast<SIZE_T>(Expected));
	Bulk.Unlock();
	DestTexture->UpdateResource();
	return true;
}
