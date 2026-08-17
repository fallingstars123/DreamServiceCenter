// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AutoUILayoutJson.h"
#include "CoreMinimal.h"

class UTexture2D;
class UWidgetBlueprint;

/** 创建界面控件流水线结果。 */
struct FAutoUIBuildWidgetResult
{
	bool bSuccess = false;
	FString Error;
	FString SourceTextureDir;
	FString SubTexDiskDir;
	FString SubTexContentPath;
	FString WidgetBlueprintPath;
	int32 BlocksExported = 0;
	int32 TexturesImported = 0;
};

/**
 * 将布局分块导出为 sub_Tex PNG，导入 Content，并生成带锚点自适应的 WidgetBlueprint。
 * widget_type：button → UButton（sub_Tex 作 Normal/Hovered/Pressed 背景）；image/panel/其它 → UImage。
 * @param SourceTexture 布局 Texture2D
 * @param LayoutSpec 已校验的布局（调用方应按纹理尺寸归一化 rect）
 * @param CropBgra 与 LayoutSpec.design_size 同尺寸的 BGRA8 源（布局图或抠图预览）
 * @param CropWidth CropBgra 宽
 * @param CropHeight CropBgra 高
 */
FAutoUIBuildWidgetResult AutoUI_BuildWidgetFromLayout(
	UTexture2D* SourceTexture,
	const FAutoUILayoutSpec& LayoutSpec,
	const TArray<uint8>& CropBgra,
	int32 CropWidth,
	int32 CropHeight);
