// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AutoUILayoutJson.h"
#include "CoreMinimal.h"

struct FAutoUILayoutBlockMergeParams
{
	/** Alpha 大于该值视为前景（0–255）。 */
	int32 ForegroundAlphaThreshold = 8;

	/** true：8 连通；false：4 连通。 */
	bool bEightConnected = true;

	/** 前景连通域像素数小于该值则忽略（与抠图「最小前景像素」一致时可传入 0 关闭）。 */
	int32 MinComponentAreaPixels = 0;
};

/**
 * 从抠图 BGRA 按 Alpha 前景连通域生成分块（每连通域一块，rect 为紧包围盒）。
 * 几何分块不依赖 AI rect；AI 语义请用 AutoUI_AttachAiMetadataToLayoutSpec。
 * @return 生成的分块数量；失败返回 0。
 */
int32 AutoUI_BuildLayoutSpecFromAlphaComponents(
	FAutoUILayoutSpec& OutSpec,
	const TArray<uint8>& Bgra,
	int32 Width,
	int32 Height,
	const FAutoUILayoutBlockMergeParams& Params,
	TArray<FString>* OutNotes = nullptr);

/**
 * 将 AI 返回的 id / widget_type 按 rect 与 Alpha 分块的最大交集面积挂到 OutSpec 上（不改变 rect）。
 */
void AutoUI_AttachAiMetadataToLayoutSpec(
	FAutoUILayoutSpec& InOutAlphaSpec,
	const FAutoUILayoutSpec& AiSpec,
	TArray<FString>* OutNotes = nullptr);

/**
 * @deprecated 旧逻辑：把 AI 多项合并到同一连通域。请改用 BuildLayoutSpecFromAlphaComponents。
 */
int32 AutoUI_MergeLayoutSpecByForegroundConnectivity(
	FAutoUILayoutSpec& InOutSpec,
	const TArray<uint8>& Bgra,
	int32 Width,
	int32 Height,
	const FAutoUILayoutBlockMergeParams& Params,
	TArray<FString>* OutNotes = nullptr);
