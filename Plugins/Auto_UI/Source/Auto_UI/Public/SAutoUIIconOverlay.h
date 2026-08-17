// Copyright Epic Games, Inc. All Rights Reserved.



#pragma once



#include "AutoUILayoutJson.h"

#include "CoreMinimal.h"

#include "Widgets/SLeafWidget.h"



/**

 * 叠在预览图上的标记层：本控件的外接矩形与「居中内层预览盒」一致，

 * 通过 FAutoUILayoutViewportTransform 将 design_size 坐标映射到预览视口像素（与底图共用视口矩阵）。

 */

class SAutoUIIconOverlay : public SLeafWidget

{

public:

	SLATE_BEGIN_ARGS(SAutoUIIconOverlay) {}

	SLATE_END_ARGS()



	void Construct(const FArguments& InArgs);



	void ClearMarkers();

	void SetMarkers(const FAutoUILayoutSpec& Spec);

	/** 更新设计坐标 → 当前预览视口的变换矩阵（由 SAutoUITab::Tick 在视口尺寸变化时调用）。 */
	void SetViewportTransform(const FAutoUILayoutViewportTransform& InTransform);

	/** true：绘制各分块 rect 裁剪框；false：在各分块 rect 左上角绘制红点。 */
	void SetDrawCropRects(bool bInDrawCropRects);

	bool GetDrawCropRects() const { return bDrawCropRects; }

	/** 已应用的 design_size（无 spec 时返回 (0,0)）。供宿主在拟合预览时读取，保证红点与图像共用同一坐标系。 */
	FIntPoint GetDesignSize() const { return DesignSize; }



	virtual FVector2D ComputeDesiredSize(float) const override;

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;



private:

	TArray<FAutoUILayoutIconEntry> Icons;

	FIntPoint DesignSize = FIntPoint::ZeroValue;

	FAutoUILayoutViewportTransform ViewportTransform;

	bool bDrawCropRects = false;

};


