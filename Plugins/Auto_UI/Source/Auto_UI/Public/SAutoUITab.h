// Copyright Epic Games, Inc. All Rights Reserved.



#pragma once



#include "AssetRegistry/AssetData.h"

#include "AutoUILayoutJson.h"

#include "CoreMinimal.h"

#include "Misc/Optional.h"

#include "UObject/StrongObjectPtr.h"

#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/SCompoundWidget.h"



class FDragDropEvent;

class UTexture2D;

class SBox;

class SButton;

class SCheckBox;

class SAutoUIIconOverlay;



/** Main Auto UI editor panel: texture preview + JSON validate (Phase 1–2). */

class SAutoUITab : public SCompoundWidget

{

public:

	SLATE_BEGIN_ARGS(SAutoUITab) {}

	SLATE_END_ARGS()



	void Construct(const FArguments& InArgs);



	/** AI HTTP 完成回调在主线程更新日志与预览标记（public：供异步 lambda 调用）。 */

	void OnAiAnalysisFinished(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec);



private:

	void OnJsonPathCommitted(const FText& Text, ETextCommit::Type CommitType);

	FReply OnBrowseJsonClicked();

	FReply OnValidateJsonClicked();

	FReply OnOpenAiSettingsClicked();

	FReply OnRunAiAnalysisClicked();

	FReply OnToggleMathMatteClicked();

	FReply OnToggleCropRectsClicked();

	FReply OnCreateUiWidgetClicked();

	bool IsCreateUiWidgetButtonEnabled() const;

	bool ResolveLayoutSpecForBuild(FAutoUILayoutSpec& OutSpec, FString& OutError) const;

	bool GatherCropSourceBgra(TArray<uint8>& OutBgra, int32& OutW, int32& OutH, FString& OutError) const;

	bool IsCropRectsButtonEnabled() const;

	FText GetCropRectsButtonLabel() const;

	bool IsMathMatteButtonEnabled() const;

	FText GetMathMatteButtonLabel() const;

	bool BuildMathMatteBgra(TArray<uint8>& OutBGRA, int32& OutWidth, int32& OutHeight, FString& OutError);

	bool BuildMathMattePngForAi(TArray<uint8>& OutPng, int32& OutWidth, int32& OutHeight, FString& OutError);

	bool UploadMathMatteBgraToPreviewTexture(const TArray<uint8>& Bgra, int32 Width, int32 Height, FString& OutError);

	bool RebuildMathMatteInternal(FString& OutError);

	void TryRebuildMatteIfVisible();

	float GetMatteToleranceSpin() const;

	void OnMatteToleranceSpinChanged(float NewValue);

	void OnMatteToleranceSpinCommitted(float NewValue, ETextCommit::Type CommitType);

	void OnMatteToleranceEndSliderMovement(float NewValue);

	float GetMatteMinFgSpinValue() const;

	void OnMatteMinFgAreaSpinChanged(float NewValue);

	void OnMatteMinFgAreaSpinCommitted(float NewValue, ETextCommit::Type CommitType);

	void OnMatteMinFgEndSliderMovement(float NewValue);

	ECheckBoxState GetMatteEightConnectedCheckState() const;

	void OnMatteEightConnectedChanged(ECheckBoxState NewState);

	void RefreshPreview();

	void SyncPreviewBrushDisplay();

	void ClearMathMatteResources();

	void SetLayoutTexture(UTexture2D* Texture);

	void ApplyOrClearIconMarkers(const TOptional<FAutoUILayoutSpec>& Spec);

	void UpdatePreviewViewportTransform();

	void SetCachedLayoutJsonForLog(const FString& JsonBody, const FString& HeaderPrefix);

	void RefreshLogLayoutJsonWithViewport();

	FIntPoint GetCurrentPreviewViewportSize() const;

	/** 从抠图 BGRA 的 Alpha 连通域生成分块（每域一块）。 */
	bool TryBuildLayoutSpecFromMatteAlpha(FAutoUILayoutSpec& OutSpec, TArray<FString>& OutNotes);

	bool SaveMattePngBytesToSavedFolder(const TArray<uint8>& PngBytes, FString& OutSavedPath, FString& OutError);



	bool AreTextureAssetsAcceptableForDrop(TArrayView<FAssetData> InAssets) const;

	void OnTextureAssetsDropped(const FDragDropEvent&, TArrayView<FAssetData> InAssets);



	TWeakObjectPtr<UTexture2D> LayoutTexture;

	/** 数学抠背景后的临时预览纹理（与 LayoutTexture 同尺寸）。 */

	TStrongObjectPtr<UTexture2D> MathMatteTexture;

	bool bShowingMathMatte = false;

	FSlateBrush PreviewBrush;

	TSharedPtr<class SImage> PreviewImage;

	TSharedPtr<SBox> PreviewSizer;

	TSharedPtr<SBox> PreviewInnerBox;

	TSharedPtr<SAutoUIIconOverlay> IconOverlay;

	TSharedPtr<SButton> CropRectsButton;

	TSharedPtr<SButton> CreateUiWidgetButton;

	TSharedPtr<SButton> MathMatteButton;

	TSharedPtr<SSpinBox<float>> MatteToleranceSpin;

	TSharedPtr<SSpinBox<float>> MatteMinFgAreaSpin;

	TSharedPtr<SCheckBox> MatteEightConnectedCheck;

	int32 MatteColorTolerance = 10;

	bool bMatteEightConnected = false;

	int32 MatteMinForegroundAreaPixels = 0;

	/** 当前预览上是否已有可绘制的布局（AI 或 JSON 校验成功后会出现红点）。 */

	bool bHasLayoutSpec = false;

	/** 当前用于预览叠层的布局（rect 保持 JSON design_size 坐标系）。 */
	TOptional<FAutoUILayoutSpec> PreviewLayoutSpec;

	/** 预览叠层是否绘制分块裁剪矩形（否则为左上角红点）。 */

	bool bShowBlockCropRects = false;

	TSharedPtr<class SMultiLineEditableTextBox> LogTextBox;

	TSharedPtr<class SEditableTextBox> JsonPathEditor;

	FString JsonPath;

	FVector2D LastPreviewAreaSize = FVector2D::ZeroVector;

	/** 用于在 Nomad Tab 整体尺寸变化时强制刷新预览缩放（避免仅依赖子控件 CachedGeometry 漏更新）。 */

	FVector2D LastOuterPanelLocalSize = FVector2D::ZeroVector;

	/** 日志区展示的布局 JSON 正文（不含 preview_viewport，注入前缓存）。 */
	FString CachedLayoutJsonBody;

	/** 日志区 JSON 段之前的说明文字（含「--- JSON ---」标题行）。 */
	FString CachedLogHeaderPrefix;

	/** 最近一次 AI 抠图 BGRA（用于连通域合并分块）。 */
	TArray<uint8> LastAiMatteBgra;

	int32 LastAiMatteW = 0;

	int32 LastAiMatteH = 0;

	/** 最近一次 AI 抠图 PNG 落盘路径（Project/Saved/AutoUI/Matte/）。 */
	FString LastMattePngSavedPath;



	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	const FSlateBrush* GetPreviewBrush() const;

};


