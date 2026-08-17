// Copyright Epic Games, Inc. All Rights Reserved.

#include "SAutoUIIconOverlay.h"

#include "Rendering/DrawElements.h"
#include "Styling/AppStyle.h"

namespace
{
	constexpr float CropBorderThickness = 2.f;
	constexpr float PivotDotSide = 10.f;

	void DrawRectOutline(
		FSlateWindowElementList& OutDrawElements,
		int32& LayerId,
		const FGeometry& AllottedGeometry,
		const FSlateBrush* Brush,
		const FLinearColor& Color,
		const float X,
		const float Y,
		const float W,
		const float H,
		const float Thickness)
	{
		const auto DrawEdge = [&](const float Bx, const float By, const float Bw, const float Bh)
		{
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				LayerId++,
				AllottedGeometry.ToPaintGeometry(FVector2f(Bw, Bh), FSlateLayoutTransform(FVector2f(Bx, By))),
				Brush,
				ESlateDrawEffect::None,
				Color);
		};

		DrawEdge(X, Y, W, Thickness);
		DrawEdge(X, Y + H - Thickness, W, Thickness);
		DrawEdge(X, Y, Thickness, H);
		DrawEdge(X + W - Thickness, Y, Thickness, H);
	}
}

void SAutoUIIconOverlay::Construct(const FArguments& InArgs)
{
}

void SAutoUIIconOverlay::ClearMarkers()
{
	Icons.Reset();
	DesignSize = FIntPoint::ZeroValue;
	ViewportTransform = FAutoUILayoutViewportTransform();
	bDrawCropRects = false;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SAutoUIIconOverlay::SetMarkers(const FAutoUILayoutSpec& Spec)
{
	Icons = Spec.Icons;
	DesignSize = Spec.DesignSize;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SAutoUIIconOverlay::SetViewportTransform(const FAutoUILayoutViewportTransform& InTransform)
{
	ViewportTransform = InTransform;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SAutoUIIconOverlay::SetDrawCropRects(const bool bInDrawCropRects)
{
	if (bDrawCropRects == bInDrawCropRects)
	{
		return;
	}

	bDrawCropRects = bInDrawCropRects;
	Invalidate(EInvalidateWidgetReason::Paint);
}

FVector2D SAutoUIIconOverlay::ComputeDesiredSize(float) const
{
	return FVector2D::ZeroVector;
}

int32 SAutoUIIconOverlay::OnPaint(
	const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	if (Icons.Num() == 0 || DesignSize.X <= 0 || DesignSize.Y <= 0)
	{
		return LayerId;
	}

	FAutoUILayoutViewportTransform Xform = ViewportTransform;
	if (!Xform.IsValid())
	{
		const FVector2D Local = AllottedGeometry.GetLocalSize();
		Xform = FAutoUILayoutViewportTransform::Make(DesignSize, Local);
	}

	if (!Xform.IsValid())
	{
		return LayerId;
	}

	const FSlateBrush* const WhiteBrush = FAppStyle::GetBrush("WhiteBrush");

	int32 CurLayer = LayerId;

	if (bDrawCropRects)
	{
		const FLinearColor FillColor(1.f, 0.f, 0.f, 0.12f);
		const FLinearColor BorderColor = FLinearColor::Red;

		for (const FAutoUILayoutIconEntry& Icon : Icons)
		{
			const FVector2D Pos = Xform.MapDesignPoint(static_cast<float>(Icon.X), static_cast<float>(Icon.Y));
			const FVector2D Size = Xform.MapDesignSize(static_cast<float>(Icon.W), static_cast<float>(Icon.H));

			if (Size.X > 0.f && Size.Y > 0.f)
			{
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					CurLayer++,
					AllottedGeometry.ToPaintGeometry(FVector2f(Size), FSlateLayoutTransform(FVector2f(Pos))),
					WhiteBrush,
					ESlateDrawEffect::None,
					FillColor);

				DrawRectOutline(
					OutDrawElements,
					CurLayer,
					AllottedGeometry,
					WhiteBrush,
					BorderColor,
					Pos.X,
					Pos.Y,
					Size.X,
					Size.Y,
					CropBorderThickness);
			}
		}
	}
	else
	{
		for (const FAutoUILayoutIconEntry& Icon : Icons)
		{
			// rect.(x,y) 为分块左上角 pivot；红点方块左上角对齐该 pivot。
			const FVector2D TopLeft = Xform.MapDesignPoint(
				static_cast<float>(Icon.X),
				static_cast<float>(Icon.Y));

			FSlateDrawElement::MakeBox(
				OutDrawElements,
				CurLayer++,
				AllottedGeometry.ToPaintGeometry(FVector2f(PivotDotSide, PivotDotSide), FSlateLayoutTransform(FVector2f(TopLeft))),
				WhiteBrush,
				ESlateDrawEffect::None,
				FLinearColor::Red);
		}
	}

	return CurLayer;
}
