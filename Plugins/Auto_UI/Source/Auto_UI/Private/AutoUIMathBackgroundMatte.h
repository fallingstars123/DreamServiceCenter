// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UTexture2D;

/** 数学抠背景可调参数（与 AI 无关）。 */
struct FAutoUIMathMatteParams
{
	/** RGB（或 RGBA）各通道差平方和阈值：sum <= ColorTolerance^2 时视为与邻接背景同色。范围 1–255。 */
	int32 ColorTolerance = 10;

	/** true：8-邻域泛洪；false：4-邻域。 */
	bool bEightConnected = false;

	/** 颜色距离是否包含 A 通道差。 */
	bool bIncludeAlphaInDistance = false;

	/**
	 * 前景连通域像素数小于该值则整块当作噪点并入背景；0 关闭。
	 * 连通性与 bEightConnected 一致。
	 */
	int32 MinForegroundAreaPixels = 0;
};

/**
 * 纯数学背景剔除：从图像四边做邻域泛洪，相邻像素颜色距离小于阈值则视为背景，输出 BGRA（背景 alpha=0）。
 */
namespace AutoUIMathBackgroundMatte
{
	/** @deprecated 使用 FAutoUIMathMatteParams::ColorTolerance 默认值。 */
	constexpr int32 DefaultColorTolerance = 10;

	bool BuildBGRAWithMatte(
		UTexture2D* SourceTexture,
		const FAutoUIMathMatteParams& Params,
		TArray<uint8>& OutBGRA,
		int32& OutWidth,
		int32& OutHeight,
		FString& OutError);

	bool UploadBGRAToTransientTexture(UTexture2D* DestTexture, int32 Width, int32 Height, const TArray<uint8>& BGRA, FString& OutError);
}
