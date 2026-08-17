// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** 单个 UI 分块（JSON 项沿用历史命名 icon；rect 左上角为 (X,Y)）。 */
struct FAutoUILayoutIconEntry
{
	FString Id;
	int32 X = 0;
	int32 Y = 0;
	int32 W = 0;
	int32 H = 0;
	FString WidgetType;
	int32 ZOrder = 0;
};

struct FAutoUILayoutSpec
{
	int32 SchemaVersion = 0;
	int32 Version = 0;
	FIntPoint DesignSize = FIntPoint::ZeroValue;
	/** 分块列表（解析自 JSON 的 blocks 或 icons）。 */
	TArray<FAutoUILayoutIconEntry> Icons;
};

/**
 * 设计坐标 (JSON design_size / rect) → 预览视口像素的仿射变换。
 * 与 SImage 将纹理非等比铺满同一视口时使用相同缩放：Sx = ViewportW/SourceW, Sy = ViewportH/SourceH。
 */
struct FAutoUILayoutViewportTransform
{
	FIntPoint SourceSize = FIntPoint::ZeroValue;
	FVector2D ViewportSize = FVector2D::ZeroVector;

	bool IsValid() const
	{
		return SourceSize.X > 0 && SourceSize.Y > 0 && ViewportSize.X > 1.f && ViewportSize.Y > 1.f;
	}

	FVector2D MapDesignPoint(const float X, const float Y) const
	{
		return FVector2D(
			X * ViewportSize.X / static_cast<float>(SourceSize.X),
			Y * ViewportSize.Y / static_cast<float>(SourceSize.Y));
	}

	FVector2D MapDesignSize(const float W, const float H) const
	{
		return FVector2D(
			W * ViewportSize.X / static_cast<float>(SourceSize.X),
			H * ViewportSize.Y / static_cast<float>(SourceSize.Y));
	}

	static FAutoUILayoutViewportTransform Make(const FIntPoint InSource, const FVector2D InViewport)
	{
		FAutoUILayoutViewportTransform T;
		T.SourceSize = InSource;
		T.ViewportSize = InViewport;
		return T;
	}
};

/** 校验严格程度：Strict 用于写资产门禁；EditorPreview 允许自动扩展 design_size 并在预览上标出分块。 */
enum class EAutoUILayoutJsonValidation : uint8
{
	Strict,
	EditorPreview,
};

/**
 * 解析并校验布局 JSON。
 * Strict：任一分块 rect 越界或重复 id 等则整体失败（OutSpec 可能仍含部分项，调用方勿用于写资产）。
 * EditorPreview：越界时尝试扩大 design_size；有至少一个合法分块则返回 true，非致命问题写入 OutErrors 作提示。
 */
bool AutoUI_ParseAndValidateLayoutJson(
	const FString& JsonString,
	FAutoUILayoutSpec& OutSpec,
	TArray<FString>& OutErrors,
	EAutoUILayoutJsonValidation Validation = EAutoUILayoutJsonValidation::Strict);

/**
 * 将布局 spec 的 rect 从 JSON 中的 design_size 坐标系缩放到纹理像素坐标系，并写回 design_size。
 * 当模型输出的 design_size 与实际上传/预览纹理尺寸不一致时，预览叠层与底图才能对齐。
 * @return 是否发生了缩放（OutNote 可选写入说明文案）
 */
bool AutoUI_NormalizeLayoutSpecToTexture(
	FAutoUILayoutSpec& InOutSpec,
	FIntPoint TextureSize,
	FString* OutNote = nullptr);

/**
 * 将 JSON 中 design_size / blocks|icons[].rect 等设计像素坐标转换为 preview_viewport 坐标系后输出。
 * 写入 preview_viewport、coordinate_space，并把 design_size 更新为视口尺寸。
 * @param SourceDesignSize 可选：解析/预览实际采用的设计尺寸（如 EditorPreview 扩展后的尺寸）；未设则从 JSON 读取。
 */
FString AutoUI_InjectPreviewViewportIntoLayoutJson(
	const FString& LayoutJson,
	FIntPoint ViewportSize,
	TOptional<FIntPoint> SourceDesignSize = TOptional<FIntPoint>());

/** 移除 preview_viewport / coordinate_space，保留设计坐标系 JSON（供缓存与再次转换）。 */
FString AutoUI_StripPreviewViewportFromLayoutJson(const FString& LayoutJson);

/** 将布局 spec 序列化为 layout_v1 JSON（blocks 数组）。 */
FString AutoUI_SerializeLayoutSpecToJson(const FAutoUILayoutSpec& Spec);
