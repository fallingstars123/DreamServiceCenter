// Copyright Epic Games, Inc. All Rights Reserved.

#include "SAutoUITab.h"

#include "AutoUILayoutJson.h"
#include "AutoUIAiVisionClient.h"
#include "AutoUILayoutBlockMerge.h"
#include "ImageCore.h"
#include "ImageUtils.h"
#include "AutoUIMathBackgroundMatte.h"
#include "AutoUIWidgetBuilder.h"
#include "SAutoUIAiSettingsDialog.h"
#include "SAutoUIIconOverlay.h"
#include "SAssetDropTarget.h"
#include "DesktopPlatformModule.h"
#include "Engine/Texture2D.h"
#include "Framework/Application/SlateApplication.h"
#include "IDesktopPlatform.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Logging/LogMacros.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SWindow.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SAutoUITab"

namespace
{
	const TCHAR* GAutoUILayoutJsonLogMarker = TEXT("--- JSON（可复制保存）---");
}

void SAutoUITab::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Title", "Auto UI — 布局预览与 JSON 校验"))
			.Font(FAppStyle::GetFontStyle("HeadingExtraSmall"))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.f, 0.f, 8.f, 0.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("AiSettings", "设置"))
				.OnClicked(this, &SAutoUITab::OnOpenAiSettingsClicked)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(8.f, 0.f, 0.f, 0.f)
			[
				SAssignNew(MathMatteButton, SButton)
				.Text(this, &SAutoUITab::GetMathMatteButtonLabel)
				.ToolTipText(LOCTEXT(
					"MathMatteTip",
					"无需 AI：从四边做颜色连通泛洪剔除背景（见下方参数：阈值、连通性等）。"
					"生成透明背景预览；再次点击恢复原图。"))
				.IsEnabled(this, &SAutoUITab::IsMathMatteButtonEnabled)
				.OnClicked(this, &SAutoUITab::OnToggleMathMatteClicked)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(8.f, 0.f, 0.f, 0.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("RunAi", "分析布局"))
				.ToolTipText(LOCTEXT(
					"RunAiTip",
					"按当前抠背景参数生成透明底 PNG 后发送 AI 识图（与是否开启预览无关）；抠图失败时回退原图。"))
				.OnClicked(this, &SAutoUITab::OnRunAiAnalysisClicked)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(8.f, 0.f, 0.f, 0.f)
			[
				SAssignNew(CropRectsButton, SButton)
				.Text(this, &SAutoUITab::GetCropRectsButtonLabel)
				.ToolTipText(LOCTEXT(
					"CropRectsTip",
					"在预览图上显示/隐藏各分块 JSON rect 的裁剪区域（红色描边与半透明填充）。需先通过 AI 分析或 JSON 校验。"))
				.IsEnabled(this, &SAutoUITab::IsCropRectsButtonEnabled)
				.OnClicked(this, &SAutoUITab::OnToggleCropRectsClicked)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(8.f, 0.f, 0.f, 0.f)
			[
				SAssignNew(CreateUiWidgetButton, SButton)
				.Text(LOCTEXT("CreateUiWidget", "创建界面控件"))
				.ToolTipText(LOCTEXT(
					"CreateUiWidgetTip",
					"将各分块裁切为 PNG 保存到源纹理目录的 sub_Tex 文件夹，并在 Content 同级目录生成 WidgetBlueprint（锚点布局，视口自适应缩放）。"))
				.IsEnabled(this, &SAutoUITab::IsCreateUiWidgetButtonEnabled)
				.OnClicked(this, &SAutoUITab::OnCreateUiWidgetClicked)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f, 2.f, 4.f, 2.f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
			.Padding(FMargin(8.f, 6.f))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.f, 0.f, 6.f, 0.f)
				[
					SNew(STextBlock).Text(LOCTEXT("MatteTolLbl", "颜色阈值"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 16.f, 0.f)
				[
					SAssignNew(MatteToleranceSpin, SSpinBox<float>)
					.MinDesiredWidth(76.f)
					.MinValue(1.f)
					.MaxValue(255.f)
					.MinSliderValue(1.f)
					.MaxSliderValue(96.f)
					.Value(this, &SAutoUITab::GetMatteToleranceSpin)
					.OnValueChanged(this, &SAutoUITab::OnMatteToleranceSpinChanged)
					.OnValueCommitted(this, &SAutoUITab::OnMatteToleranceSpinCommitted)
					.OnEndSliderMovement(this, &SAutoUITab::OnMatteToleranceEndSliderMovement)
					.ToolTipText(LOCTEXT("MatteTolTip", "相邻像素与当前背景边界颜色差的平方和上限（与阈值 T 比较：≤ T²）。越大越容易把前景并进背景。"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(8.f, 0.f, 6.f, 0.f)
				[
					SNew(STextBlock).Text(LOCTEXT("MatteEightLbl", "8连通"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 16.f, 0.f)
				[
					SAssignNew(MatteEightConnectedCheck, SCheckBox)
					.IsChecked(this, &SAutoUITab::GetMatteEightConnectedCheckState)
					.OnCheckStateChanged(this, &SAutoUITab::OnMatteEightConnectedChanged)
					.ToolTipText(LOCTEXT("MatteEightTip", "勾选：含对角相邻，泛洪更易“漏”进细缝；不勾选：仅上下左右 4 邻域。"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(8.f, 0.f, 6.f, 0.f)
				[
					SNew(STextBlock).Text(LOCTEXT("MatteMinFgLbl", "最小前景像素"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(MatteMinFgAreaSpin, SSpinBox<float>)
					.MinDesiredWidth(104.f)
					.MinValue(0.f)
					.MaxValue(2000000.f)
					.MinSliderValue(0.f)
					.MaxSliderValue(5000.f)
					.Delta(1.f)
					.Value(this, &SAutoUITab::GetMatteMinFgSpinValue)
					.OnValueChanged(this, &SAutoUITab::OnMatteMinFgAreaSpinChanged)
					.OnValueCommitted(this, &SAutoUITab::OnMatteMinFgAreaSpinCommitted)
					.OnEndSliderMovement(this, &SAutoUITab::OnMatteMinFgEndSliderMovement)
					.ToolTipText(LOCTEXT("MatteMinFgTip", "前景连通域小于该像素数则整块当作噪点并入背景；0 关闭。连通性与「8连通」一致。"))
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(SAssetDropTarget)
			.OnAreAssetsAcceptableForDrop(this, &SAutoUITab::AreTextureAssetsAcceptableForDrop)
			.OnAssetsDropped(this, &SAutoUITab::OnTextureAssetsDropped)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
				.Padding(FMargin(8.f))
				[
					SNew(STextBlock)
					.Text(LOCTEXT("DropHint", "从内容浏览器将 Texture2D 拖放到此行或下方预览区"))
					.AutoWrapText(true)
				]
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		.Padding(4.f)
		[
			SNew(SBox)
			.MinDesiredHeight(200.f)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
					.Padding(4.f)
					[
						// 预览区：内外层均 Fill，图像与红点叠层拉伸铺满整个可用宽高（非等比）。
						SAssignNew(PreviewSizer, SBox)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SAssignNew(PreviewInnerBox, SBox)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SAssignNew(PreviewImage, SImage)
									.Image(this, &SAutoUITab::GetPreviewBrush)
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SAssignNew(IconOverlay, SAutoUIIconOverlay)
									.Visibility(EVisibility::HitTestInvisible)
								]
							]
						]
					]
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SAssetDropTarget)
					.OnAreAssetsAcceptableForDrop(this, &SAutoUITab::AreTextureAssetsAcceptableForDrop)
					.OnAssetsDropped(this, &SAutoUITab::OnTextureAssetsDropped)
					[
						SNew(SBorder)
						.BorderImage(FAppStyle::GetBrush("NoBorder"))
						.Padding(0.f)
						[
							SNew(SColorBlock)
							.Color(FLinearColor(0.f, 0.f, 0.f, 0.02f))
						]
					]
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 4.f, 0.f)
			[
				SAssignNew(JsonPathEditor, SEditableTextBox)
				.HintText(LOCTEXT("JsonHint", "布局 JSON 路径（.json）"))
				.Text(FText::FromString(JsonPath))
				.OnTextCommitted(this, &SAutoUITab::OnJsonPathCommitted)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.f, 0.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("BrowseJson", "浏览…"))
				.OnClicked(this, &SAutoUITab::OnBrowseJsonClicked)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("ValidateJson", "校验 JSON"))
				.OnClicked(this, &SAutoUITab::OnValidateJsonClicked)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(SExpandableArea)
			.AreaTitle(LOCTEXT("LogJsonExpandTitle", "日志与 JSON（可折叠）"))
			.InitiallyCollapsed(false)
			.BorderBackgroundColor(FSlateColor(FLinearColor(0.02f, 0.02f, 0.02f, 1.f)))
			.BodyBorderBackgroundColor(FSlateColor(FLinearColor(0.04f, 0.04f, 0.04f, 1.f)))
			.Padding(FMargin(4.f))
			.MaxHeight(320.f)
			.BodyContent()
			[
				SNew(SBox)
				.HeightOverride(280.f)
				[
					SAssignNew(LogTextBox, SMultiLineEditableTextBox)
					.IsReadOnly(true)
					.AutoWrapText(false)
					.Text(LOCTEXT("LogPlaceholder", "校验结果将显示在此处。"))
				]
			]
		]
	];

	PreviewBrush.DrawAs = ESlateBrushDrawType::Image;
	PreviewBrush.Tiling = ESlateBrushTileType::NoTile;
}

void SAutoUITab::OnJsonPathCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	JsonPath = Text.ToString();
}

FReply SAutoUITab::OnBrowseJsonClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		return FReply::Handled();
	}

	const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(AsShared());

	TArray<FString> OpenFilenames;
	const FString Title = LOCTEXT("PickJsonTitle", "选择布局 JSON").ToString();
	const FString DefaultPath = FPaths::ProjectContentDir();
	const FString FileTypes = TEXT("JSON Files|*.json|All Files|*.*");

	if (DesktopPlatform->OpenFileDialog(ParentWindowWindowHandle, Title, DefaultPath, TEXT(""), FileTypes, EFileDialogFlags::None, OpenFilenames) && OpenFilenames.Num() > 0)
	{
		JsonPath = OpenFilenames[0];
		if (JsonPathEditor.IsValid())
		{
			JsonPathEditor->SetText(FText::FromString(JsonPath));
		}
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(FString::Printf(TEXT("已选择 JSON：%s"), *JsonPath)));
		}
	}

	return FReply::Handled();
}

FReply SAutoUITab::OnValidateJsonClicked()
{
	if (JsonPath.IsEmpty() || !FPaths::FileExists(JsonPath))
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(LOCTEXT("JsonMissing", "请先选择有效的 JSON 文件路径。"));
		}
		ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>());
		return FReply::Handled();
	}

	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *JsonPath))
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(FString::Printf(TEXT("无法读取文件：%s"), *JsonPath)));
		}
		ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>());
		return FReply::Handled();
	}

	FAutoUILayoutSpec Spec;
	TArray<FString> Errors;
	const bool bStrictOk = AutoUI_ParseAndValidateLayoutJson(
		JsonString,
		Spec,
		Errors,
		EAutoUILayoutJsonValidation::Strict);

	if (!bStrictOk)
	{
		Spec = FAutoUILayoutSpec();
		Errors.Reset();
		const bool bPreviewOk = AutoUI_ParseAndValidateLayoutJson(
			JsonString,
			Spec,
			Errors,
			EAutoUILayoutJsonValidation::EditorPreview);

		FString Msg;
		if (bPreviewOk && Spec.Icons.Num() > 0)
		{
			Msg = FString::Printf(
				TEXT("严格校验未通过，但已在预览上标出 %d 个分块（预览模式）。\n"),
				Spec.Icons.Num());
			if (Errors.Num() > 0)
			{
				Msg += TEXT("\n提示：\n");
				for (const FString& Line : Errors)
				{
					Msg += Line + TEXT("\n");
				}
			}
		}
		else
		{
			Msg = TEXT("校验失败：\n");
			for (const FString& Line : Errors)
			{
				Msg += Line + TEXT("\n");
			}
			if (LogTextBox.IsValid())
			{
				LogTextBox->SetText(FText::FromString(Msg));
			}
			ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>());
			return FReply::Handled();
		}

		const FString Header = Msg + FString::Printf(TEXT("\n%s\n"), GAutoUILayoutJsonLogMarker);
		SetCachedLayoutJsonForLog(AutoUI_StripPreviewViewportFromLayoutJson(JsonString), Header);
		ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>(Spec));
		return FReply::Handled();
	}

	FString Msg = FString::Printf(
		TEXT("校验通过。\nschema_version=%d\nversion=%d\ndesign_size=%dx%d\n分块数=%d\n"),
		Spec.SchemaVersion,
		Spec.Version,
		Spec.DesignSize.X,
		Spec.DesignSize.Y,
		Spec.Icons.Num());
	Msg += FString::Printf(TEXT("%s\n"), GAutoUILayoutJsonLogMarker);

	const FString Header = Msg;
	SetCachedLayoutJsonForLog(AutoUI_StripPreviewViewportFromLayoutJson(JsonString), Header);
	ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>(Spec));

	return FReply::Handled();
}

FReply SAutoUITab::OnOpenAiSettingsClicked()
{
	const TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(LOCTEXT("AiWinTitle", "Auto UI — AI 服务设置"))
		.ClientSize(FVector2D(640.f, 520.f))
		.SizingRule(ESizingRule::UserSized)
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			SNew(SAutoUIAiSettingsDialog)
		];

	const TSharedPtr<SWindow> Parent = FSlateApplication::Get().FindWidgetWindow(AsShared());
	FSlateApplication::Get().AddModalWindow(Window, Parent);
	return FReply::Handled();
}

FReply SAutoUITab::OnRunAiAnalysisClicked()
{
	if (!LayoutTexture.IsValid())
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(LOCTEXT("NeedTexFirst", "请先拖入一张布局 Texture2D。"));
		}
		return FReply::Handled();
	}

	const TWeakPtr<SAutoUITab> WeakSelf(StaticCastSharedRef<SAutoUITab>(AsShared()).ToWeakPtr());

	TArray<uint8> MattePng;
	int32 MatteW = 0;
	int32 MatteH = 0;
	FString MatteErr;
	if (BuildMathMattePngForAi(MattePng, MatteW, MatteH, MatteErr))
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(LOCTEXT("AiRunningMatte", "正在用数学抠背景透明 PNG 请求 AI 分析，请稍候…"));
		}

		AutoUIAiVision::RequestLayoutJsonFromPng(MattePng, MatteW, MatteH, [WeakSelf](bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)
		{
			if (const TSharedPtr<SAutoUITab> Tab = WeakSelf.Pin())
			{
				Tab->OnAiAnalysisFinished(bOk, MoveTemp(Message), MoveTemp(Spec));
			}
		});
	}
	else
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(FString::Printf(
				TEXT("抠背景失败，正在用原图请求 AI…\n%s"),
				*MatteErr)));
		}

		AutoUIAiVision::RequestLayoutJsonFromImage(LayoutTexture.Get(), [WeakSelf, MatteErr](bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)
		{
			if (const TSharedPtr<SAutoUITab> Tab = WeakSelf.Pin())
			{
				if (bOk)
				{
					Message = FString::Printf(TEXT("注意：本次识图使用原图（抠背景失败：%s）。\n\n"), *MatteErr) + Message;
				}
				Tab->OnAiAnalysisFinished(bOk, MoveTemp(Message), MoveTemp(Spec));
			}
		});
	}

	return FReply::Handled();
}

bool SAutoUITab::IsCropRectsButtonEnabled() const
{
	return bHasLayoutSpec && IconOverlay.IsValid() && IconOverlay->GetDesignSize().X > 0;
}

FText SAutoUITab::GetCropRectsButtonLabel() const
{
	return bShowBlockCropRects ? LOCTEXT("CropRectsHide", "隐藏裁剪区域") : LOCTEXT("CropRectsShow", "查看裁剪区域");
}

FReply SAutoUITab::OnToggleCropRectsClicked()
{
	if (!IsCropRectsButtonEnabled())
	{
		return FReply::Handled();
	}

	bShowBlockCropRects = !bShowBlockCropRects;

	if (IconOverlay.IsValid())
	{
		IconOverlay->SetDrawCropRects(bShowBlockCropRects);
	}

	if (CropRectsButton.IsValid())
	{
		CropRectsButton->Invalidate(EInvalidateWidgetReason::Paint);
	}

	return FReply::Handled();
}

bool SAutoUITab::IsCreateUiWidgetButtonEnabled() const
{
	if (!LayoutTexture.IsValid())
	{
		return false;
	}

	if (bHasLayoutSpec && PreviewLayoutSpec.IsSet() && PreviewLayoutSpec->Icons.Num() > 0)
	{
		return true;
	}

	if (!CachedLayoutJsonBody.IsEmpty())
	{
		return true;
	}

	return !JsonPath.IsEmpty() && FPaths::FileExists(JsonPath);
}

bool SAutoUITab::ResolveLayoutSpecForBuild(FAutoUILayoutSpec& OutSpec, FString& OutError) const
{
	OutSpec = FAutoUILayoutSpec();
	OutError.Reset();

	if (PreviewLayoutSpec.IsSet() && PreviewLayoutSpec->Icons.Num() > 0)
	{
		OutSpec = PreviewLayoutSpec.GetValue();
		return true;
	}

	FString JsonString = CachedLayoutJsonBody;
	if (JsonString.IsEmpty() && !JsonPath.IsEmpty() && FPaths::FileExists(JsonPath))
	{
		if (!FFileHelper::LoadFileToString(JsonString, *JsonPath))
		{
			OutError = FString::Printf(TEXT("无法读取 JSON：%s"), *JsonPath);
			return false;
		}
	}

	if (JsonString.IsEmpty())
	{
		OutError = TEXT("无可用布局：请先校验 JSON 或完成 AI 分析。");
		return false;
	}

	JsonString = AutoUI_StripPreviewViewportFromLayoutJson(JsonString);

	TArray<FString> Errors;
	if (AutoUI_ParseAndValidateLayoutJson(
			JsonString,
			OutSpec,
			Errors,
			EAutoUILayoutJsonValidation::Strict))
	{
		return OutSpec.Icons.Num() > 0;
	}

	OutSpec = FAutoUILayoutSpec();
	Errors.Reset();
	if (AutoUI_ParseAndValidateLayoutJson(
			JsonString,
			OutSpec,
			Errors,
			EAutoUILayoutJsonValidation::EditorPreview)
		&& OutSpec.Icons.Num() > 0)
	{
		return true;
	}

	OutError = TEXT("布局 JSON 校验失败。");
	for (const FString& Line : Errors)
	{
		OutError += TEXT("\n") + Line;
	}
	return false;
}

bool SAutoUITab::GatherCropSourceBgra(TArray<uint8>& OutBgra, int32& OutW, int32& OutH, FString& OutError) const
{
	OutBgra.Reset();
	OutW = 0;
	OutH = 0;
	OutError.Reset();

	if (!LayoutTexture.IsValid())
	{
		OutError = TEXT("未选择纹理。");
		return false;
	}

	if (LastAiMatteBgra.Num() > 0 && LastAiMatteW > 0 && LastAiMatteH > 0)
	{
		OutBgra = LastAiMatteBgra;
		OutW = LastAiMatteW;
		OutH = LastAiMatteH;
		return true;
	}

	if (bShowingMathMatte)
	{
		TArray<uint8> MatteBgra;
		if (const_cast<SAutoUITab*>(this)->BuildMathMatteBgra(MatteBgra, OutW, OutH, OutError))
		{
			OutBgra = MoveTemp(MatteBgra);
			return true;
		}
	}

	FImage SourceImage;
	if (!FImageUtils::GetTexture2DSourceImage(LayoutTexture.Get(), SourceImage))
	{
		OutError = TEXT("无法读取布局纹理源像素。");
		return false;
	}

	OutW = SourceImage.SizeX;
	OutH = SourceImage.SizeY;
	const int32 Bytes = OutW * OutH * 4;
	if (SourceImage.RawData.Num() < Bytes)
	{
		OutError = TEXT("纹理源数据尺寸不足。");
		return false;
	}

	OutBgra.SetNumUninitialized(Bytes);
	FMemory::Memcpy(OutBgra.GetData(), SourceImage.RawData.GetData(), Bytes);
	return true;
}

FReply SAutoUITab::OnCreateUiWidgetClicked()
{
	if (!LayoutTexture.IsValid())
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(LOCTEXT("CreateUiNeedTex", "请先拖入布局 Texture2D。"));
		}
		return FReply::Handled();
	}

	FAutoUILayoutSpec Spec;
	FString SpecError;
	if (!ResolveLayoutSpecForBuild(Spec, SpecError))
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(SpecError));
		}
		return FReply::Handled();
	}

	TArray<uint8> CropBgra;
	int32 CropW = 0;
	int32 CropH = 0;
	FString CropError;
	if (!GatherCropSourceBgra(CropBgra, CropW, CropH, CropError))
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(CropError));
		}
		return FReply::Handled();
	}

	FString NormNote;
	AutoUI_NormalizeLayoutSpecToTexture(Spec, FIntPoint(CropW, CropH), &NormNote);

	if (LogTextBox.IsValid())
	{
		LogTextBox->SetText(LOCTEXT("CreateUiRunning", "正在导出 sub_Tex 并创建 WidgetBlueprint…"));
	}

	const FAutoUIBuildWidgetResult BuildResult = AutoUI_BuildWidgetFromLayout(
		LayoutTexture.Get(),
		Spec,
		CropBgra,
		CropW,
		CropH);

	if (!LogTextBox.IsValid())
	{
		return FReply::Handled();
	}

	if (!BuildResult.bSuccess)
	{
		LogTextBox->SetText(FText::FromString(FString::Printf(TEXT("创建界面控件失败：\n%s"), *BuildResult.Error)));
		return FReply::Handled();
	}

	FString Msg = FString::Printf(
		TEXT("创建界面控件完成。\n")
		TEXT("分块 PNG：%d 张 → %s\n")
		TEXT("Content 子纹理：%d 张 → %s\n")
		TEXT("WidgetBlueprint：%s\n"),
		BuildResult.BlocksExported,
		*BuildResult.SubTexDiskDir,
		BuildResult.TexturesImported,
		*BuildResult.SubTexContentPath,
		*BuildResult.WidgetBlueprintPath);

	if (!NormNote.IsEmpty())
	{
		Msg += NormNote + TEXT("\n");
	}

	LogTextBox->SetText(FText::FromString(Msg));
	return FReply::Handled();
}

bool SAutoUITab::IsMathMatteButtonEnabled() const
{
	return LayoutTexture.IsValid();
}

FText SAutoUITab::GetMathMatteButtonLabel() const
{
	return bShowingMathMatte ? LOCTEXT("MathMatteOff", "恢复原图") : LOCTEXT("MathMatteOn", "抠背景");
}

FReply SAutoUITab::OnToggleMathMatteClicked()
{
	if (!LayoutTexture.IsValid())
	{
		return FReply::Handled();
	}

	if (bShowingMathMatte)
	{
		bShowingMathMatte = false;
	}
	else
	{
		FString Err;
		if (!RebuildMathMatteInternal(Err))
		{
			if (LogTextBox.IsValid())
			{
				LogTextBox->SetText(FText::FromString(FString::Printf(TEXT("数学抠背景失败：\n%s"), *Err)));
			}
			return FReply::Handled();
		}

		bShowingMathMatte = true;

		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(LOCTEXT("MatteOk", "已生成数学抠背景预览。可调整下方参数后拖动滑块结束或失焦以更新；再次点击按钮恢复原图。"));
		}
	}

	SyncPreviewBrushDisplay();

	if (PreviewImage.IsValid())
	{
		PreviewImage->Invalidate(EInvalidateWidgetReason::Paint);
	}

	if (MathMatteButton.IsValid())
	{
		MathMatteButton->Invalidate(EInvalidateWidgetReason::Paint);
	}

	return FReply::Handled();
}

bool SAutoUITab::BuildMathMatteBgra(TArray<uint8>& OutBGRA, int32& OutWidth, int32& OutHeight, FString& OutError)
{
	OutBGRA.Reset();
	OutWidth = 0;
	OutHeight = 0;

	UTexture2D* Src = LayoutTexture.Get();
	if (!Src)
	{
		OutError = TEXT("未选择纹理。");
		return false;
	}

	FAutoUIMathMatteParams Params;
	Params.ColorTolerance = FMath::Clamp(MatteColorTolerance, 1, 255);
	Params.bEightConnected = bMatteEightConnected;
	Params.bIncludeAlphaInDistance = false;
	Params.MinForegroundAreaPixels = FMath::Clamp(MatteMinForegroundAreaPixels, 0, 2000000);

	return AutoUIMathBackgroundMatte::BuildBGRAWithMatte(Src, Params, OutBGRA, OutWidth, OutHeight, OutError);
}

bool SAutoUITab::UploadMathMatteBgraToPreviewTexture(const TArray<uint8>& Bgra, const int32 W, const int32 H, FString& OutError)
{
	UTexture2D* Src = LayoutTexture.Get();
	if (!Src)
	{
		OutError = TEXT("未选择纹理。");
		return false;
	}

	if (MathMatteTexture.IsValid() && MathMatteTexture->GetSizeX() == W && MathMatteTexture->GetSizeY() == H)
	{
		return AutoUIMathBackgroundMatte::UploadBGRAToTransientTexture(MathMatteTexture.Get(), W, H, Bgra, OutError);
	}

	UTexture2D* NewTex = UTexture2D::CreateTransient(W, H, PF_B8G8R8A8);
	if (!NewTex)
	{
		OutError = TEXT("无法创建临时纹理。");
		return false;
	}

	NewTex->MipGenSettings = TMGS_NoMipmaps;
	NewTex->CompressionSettings = TC_Default;
	NewTex->NeverStream = true;
	NewTex->SRGB = Src->SRGB;

	if (!AutoUIMathBackgroundMatte::UploadBGRAToTransientTexture(NewTex, W, H, Bgra, OutError))
	{
		return false;
	}

	MathMatteTexture.Reset(NewTex);
	return true;
}

bool SAutoUITab::BuildMathMattePngForAi(TArray<uint8>& OutPng, int32& OutWidth, int32& OutHeight, FString& OutError)
{
	OutPng.Reset();
	OutWidth = 0;
	OutHeight = 0;

	TArray<uint8> Bgra;
	if (!BuildMathMatteBgra(Bgra, OutWidth, OutHeight, OutError))
	{
		return false;
	}

	LastAiMatteBgra = Bgra;
	LastAiMatteW = OutWidth;
	LastAiMatteH = OutHeight;

	FImage Image;
	Image.Init(OutWidth, OutHeight, ERawImageFormat::BGRA8, EGammaSpace::sRGB);
	if (Image.RawData.Num() < Bgra.Num())
	{
		OutError = TEXT("抠图缓冲与图像尺寸不匹配。");
		return false;
	}

	FMemory::Memcpy(Image.RawData.GetData(), Bgra.GetData(), Bgra.Num());

	TArray64<uint8> PngBytes64;
	if (!FImageUtils::CompressImage(PngBytes64, TEXT("png"), Image) || PngBytes64.Num() == 0)
	{
		OutError = TEXT("无法将抠背景结果压缩为 PNG。");
		return false;
	}

	if (PngBytes64.Num() > MAX_int32)
	{
		OutError = TEXT("抠背景 PNG 体积过大。");
		return false;
	}

	OutPng.Append(PngBytes64.GetData(), static_cast<int32>(PngBytes64.Num()));

	FString SavedPath;
	FString SaveErr;
	if (SaveMattePngBytesToSavedFolder(OutPng, SavedPath, SaveErr))
	{
		LastMattePngSavedPath = SavedPath;
	}
	else
	{
		LastMattePngSavedPath.Reset();
		UE_LOG(LogTemp, Warning, TEXT("AutoUI: 抠图 PNG 保存失败: %s"), *SaveErr);
	}

	if (!UploadMathMatteBgraToPreviewTexture(Bgra, OutWidth, OutHeight, OutError))
	{
		return false;
	}

	bShowingMathMatte = true;
	SyncPreviewBrushDisplay();
	if (PreviewImage.IsValid())
	{
		PreviewImage->Invalidate(EInvalidateWidgetReason::Paint);
	}
	if (MathMatteButton.IsValid())
	{
		MathMatteButton->Invalidate(EInvalidateWidgetReason::Paint);
	}

	return true;
}

bool SAutoUITab::RebuildMathMatteInternal(FString& OutError)
{
	TArray<uint8> Bgra;
	int32 W = 0;
	int32 H = 0;
	if (!BuildMathMatteBgra(Bgra, W, H, OutError))
	{
		return false;
	}

	return UploadMathMatteBgraToPreviewTexture(Bgra, W, H, OutError);
}

void SAutoUITab::TryRebuildMatteIfVisible()
{
	if (!bShowingMathMatte || !LayoutTexture.IsValid())
	{
		return;
	}

	FString Err;
	if (!RebuildMathMatteInternal(Err))
	{
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(FString::Printf(TEXT("数学抠背景更新失败：\n%s"), *Err)));
		}
		return;
	}

	SyncPreviewBrushDisplay();

	if (PreviewImage.IsValid())
	{
		PreviewImage->Invalidate(EInvalidateWidgetReason::Paint);
	}
}

float SAutoUITab::GetMatteToleranceSpin() const
{
	return static_cast<float>(MatteColorTolerance);
}

void SAutoUITab::OnMatteToleranceSpinChanged(const float NewValue)
{
	MatteColorTolerance = FMath::Clamp(FMath::RoundToInt(NewValue), 1, 255);
}

void SAutoUITab::OnMatteToleranceSpinCommitted(const float NewValue, ETextCommit::Type /*CommitType*/)
{
	OnMatteToleranceSpinChanged(NewValue);
	TryRebuildMatteIfVisible();
}

void SAutoUITab::OnMatteToleranceEndSliderMovement(float /*NewValue*/)
{
	TryRebuildMatteIfVisible();
}

float SAutoUITab::GetMatteMinFgSpinValue() const
{
	return static_cast<float>(MatteMinForegroundAreaPixels);
}

void SAutoUITab::OnMatteMinFgAreaSpinChanged(const float NewValue)
{
	MatteMinForegroundAreaPixels = FMath::Clamp(FMath::RoundToInt(NewValue), 0, 2000000);
}

void SAutoUITab::OnMatteMinFgAreaSpinCommitted(const float NewValue, ETextCommit::Type /*CommitType*/)
{
	OnMatteMinFgAreaSpinChanged(NewValue);
	TryRebuildMatteIfVisible();
}

void SAutoUITab::OnMatteMinFgEndSliderMovement(float /*NewValue*/)
{
	TryRebuildMatteIfVisible();
}

ECheckBoxState SAutoUITab::GetMatteEightConnectedCheckState() const
{
	return bMatteEightConnected ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SAutoUITab::OnMatteEightConnectedChanged(const ECheckBoxState NewState)
{
	bMatteEightConnected = (NewState == ECheckBoxState::Checked);
	TryRebuildMatteIfVisible();
}

bool SAutoUITab::TryBuildLayoutSpecFromMatteAlpha(FAutoUILayoutSpec& OutSpec, TArray<FString>& OutNotes)
{
	TArray<uint8> Bgra;
	int32 W = 0;
	int32 H = 0;

	if (LastAiMatteBgra.Num() > 0 && LastAiMatteW > 0 && LastAiMatteH > 0)
	{
		Bgra = LastAiMatteBgra;
		W = LastAiMatteW;
		H = LastAiMatteH;
	}
	else
	{
		FString Err;
		if (!BuildMathMatteBgra(Bgra, W, H, Err))
		{
			OutNotes.Add(FString::Printf(TEXT("Alpha 分块跳过：无法生成抠图掩码（%s）。"), *Err));
			return false;
		}
	}

	FAutoUILayoutBlockMergeParams Params;
	Params.ForegroundAlphaThreshold = 1;
	Params.bEightConnected = bMatteEightConnected;
	Params.MinComponentAreaPixels = MatteMinForegroundAreaPixels;

	return AutoUI_BuildLayoutSpecFromAlphaComponents(OutSpec, Bgra, W, H, Params, &OutNotes) > 0;
}

bool SAutoUITab::SaveMattePngBytesToSavedFolder(const TArray<uint8>& PngBytes, FString& OutSavedPath, FString& OutError)
{
	OutSavedPath.Reset();
	if (PngBytes.Num() == 0)
	{
		OutError = TEXT("PNG 数据为空。");
		return false;
	}

	const FString Dir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("AutoUI/Matte"));
	if (!IFileManager::Get().MakeDirectory(*Dir, true))
	{
		OutError = FString::Printf(TEXT("无法创建目录：%s"), *Dir);
		return false;
	}

	const FString TexName = LayoutTexture.IsValid() ? LayoutTexture->GetName() : TEXT("layout");
	const FString FileName = FString::Printf(
		TEXT("%s_%s.png"),
		*TexName,
		*FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S")));
	OutSavedPath = FPaths::Combine(Dir, FileName);

	if (!FFileHelper::SaveArrayToFile(PngBytes, *OutSavedPath))
	{
		OutError = FString::Printf(TEXT("写入失败：%s"), *OutSavedPath);
		OutSavedPath.Reset();
		return false;
	}

	return true;
}

void SAutoUITab::OnAiAnalysisFinished(bool /*bOk*/, FString Message, TOptional<FAutoUILayoutSpec> Spec)
{
	if (Spec.IsSet())
	{
		const FAutoUILayoutSpec AiSpec = Spec.GetValue();
		FAutoUILayoutSpec BlockSpec;
		TArray<FString> BlockNotes;
		const bool bBuiltFromAlpha = TryBuildLayoutSpecFromMatteAlpha(BlockSpec, BlockNotes);

		FAutoUILayoutSpec PreviewSpec = AiSpec;
		FString LogHeader;
		FString JsonBody;

		if (bBuiltFromAlpha && BlockSpec.Icons.Num() > 0)
		{
			AutoUI_AttachAiMetadataToLayoutSpec(BlockSpec, AiSpec, &BlockNotes);
			PreviewSpec = BlockSpec;

			LogHeader = FString::Printf(
				TEXT("AI 分析完成（识图输入：数学抠背景透明 PNG）。\n")
				TEXT("分块规则：抠图 Alpha 前景连通域，每域 1 块（几何不采用 AI rect 合并）。\n")
				TEXT("预览分块数=%d；AI 返回语义项=%d。\n"),
				BlockSpec.Icons.Num(),
				AiSpec.Icons.Num());

			if (!LastMattePngSavedPath.IsEmpty())
			{
				LogHeader += FString::Printf(TEXT("抠图 PNG 已保存：%s\n"), *LastMattePngSavedPath);
			}

			for (const FString& Line : BlockNotes)
			{
				LogHeader += Line + TEXT("\n");
			}

			LogHeader += FString::Printf(TEXT("\n%s\n"), GAutoUILayoutJsonLogMarker);
			JsonBody = AutoUI_SerializeLayoutSpecToJson(BlockSpec);
			SetCachedLayoutJsonForLog(JsonBody, LogHeader);
		}
		else
		{
			if (BlockNotes.Num() > 0)
			{
				Message += TEXT("\n");
				for (const FString& Line : BlockNotes)
				{
					Message += Line + TEXT("\n");
				}
				Message += TEXT("（无法从抠图 Alpha 分块，预览仍使用 AI 原始 rect。）\n");
			}

			const int32 MarkerIndex = Message.Find(GAutoUILayoutJsonLogMarker, ESearchCase::IgnoreCase, ESearchDir::FromStart);
			if (MarkerIndex != INDEX_NONE)
			{
				const int32 MarkerLen = FCString::Strlen(GAutoUILayoutJsonLogMarker);
				LogHeader = Message.Left(MarkerIndex + MarkerLen) + TEXT("\n");
				JsonBody = Message.Mid(MarkerIndex + MarkerLen).TrimStartAndEnd();
				SetCachedLayoutJsonForLog(AutoUI_StripPreviewViewportFromLayoutJson(JsonBody), LogHeader);
			}
			else if (LogTextBox.IsValid())
			{
				LogTextBox->SetText(FText::FromString(Message));
			}
		}

		ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>(PreviewSpec));
	}
	else
	{
		CachedLayoutJsonBody.Reset();
		CachedLogHeaderPrefix.Reset();
		if (LogTextBox.IsValid())
		{
			LogTextBox->SetText(FText::FromString(Message));
		}
		ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>());
	}
}

void SAutoUITab::ApplyOrClearIconMarkers(const TOptional<FAutoUILayoutSpec>& Spec)
{
	const bool bHadSpec = bHasLayoutSpec;
	bHasLayoutSpec = Spec.IsSet();
	PreviewLayoutSpec.Reset();

	if (!bHasLayoutSpec)
	{
		bShowBlockCropRects = false;
		CachedLayoutJsonBody.Reset();
		CachedLogHeaderPrefix.Reset();
	}

	if (Spec.IsSet())
	{
		PreviewLayoutSpec = Spec.GetValue();
	}

	if (!IconOverlay.IsValid())
	{
		return;
	}

	if (PreviewLayoutSpec.IsSet())
	{
		IconOverlay->SetMarkers(PreviewLayoutSpec.GetValue());
		IconOverlay->SetDrawCropRects(bShowBlockCropRects);
	}
	else
	{
		IconOverlay->ClearMarkers();
	}

	// spec 的有无切换会改变 Tick 中的拟合参考（design_size ↔ 纹理像素），
	// 强制下一帧重算 inner size，否则可能停留在上一参考下计算的尺寸。
	if (bHadSpec != bHasLayoutSpec)
	{
		LastPreviewAreaSize = FVector2D::ZeroVector;
		if (PreviewInnerBox.IsValid())
		{
			PreviewInnerBox->Invalidate(EInvalidateWidgetReason::Layout);
		}
	}

	if (MathMatteButton.IsValid())
	{
		MathMatteButton->Invalidate(EInvalidateWidgetReason::Paint);
	}

	if (CropRectsButton.IsValid())
	{
		CropRectsButton->Invalidate(EInvalidateWidgetReason::Paint);
	}

	UpdatePreviewViewportTransform();
}

void SAutoUITab::UpdatePreviewViewportTransform()
{
	if (!IconOverlay.IsValid() || !PreviewLayoutSpec.IsSet() || !PreviewInnerBox.IsValid())
	{
		return;
	}

	FVector2D Viewport = PreviewInnerBox->GetCachedGeometry().GetLocalSize();
	if (Viewport.X <= 1.f || Viewport.Y <= 1.f)
	{
		if (PreviewSizer.IsValid())
		{
			Viewport = PreviewSizer->GetCachedGeometry().GetLocalSize();
		}
	}

	if (Viewport.X <= 1.f || Viewport.Y <= 1.f)
	{
		return;
	}

	const FAutoUILayoutViewportTransform Xform =
		FAutoUILayoutViewportTransform::Make(PreviewLayoutSpec.GetValue().DesignSize, Viewport);
	IconOverlay->SetViewportTransform(Xform);
}

FIntPoint SAutoUITab::GetCurrentPreviewViewportSize() const
{
	if (LastPreviewAreaSize.X > 1.f && LastPreviewAreaSize.Y > 1.f)
	{
		return FIntPoint(
			FMath::Max(1, FMath::RoundToInt(LastPreviewAreaSize.X)),
			FMath::Max(1, FMath::RoundToInt(LastPreviewAreaSize.Y)));
	}

	if (PreviewInnerBox.IsValid())
	{
		const FVector2D Local = PreviewInnerBox->GetCachedGeometry().GetLocalSize();
		if (Local.X > 1.f && Local.Y > 1.f)
		{
			return FIntPoint(FMath::Max(1, FMath::RoundToInt(Local.X)), FMath::Max(1, FMath::RoundToInt(Local.Y)));
		}
	}

	return FIntPoint::ZeroValue;
}

void SAutoUITab::SetCachedLayoutJsonForLog(const FString& JsonBody, const FString& HeaderPrefix)
{
	CachedLayoutJsonBody = JsonBody;
	CachedLogHeaderPrefix = HeaderPrefix;
	RefreshLogLayoutJsonWithViewport();
}

void SAutoUITab::RefreshLogLayoutJsonWithViewport()
{
	if (!LogTextBox.IsValid() || CachedLayoutJsonBody.IsEmpty())
	{
		return;
	}

	const FIntPoint Viewport = GetCurrentPreviewViewportSize();
	TOptional<FIntPoint> SourceDesign;
	if (PreviewLayoutSpec.IsSet())
	{
		const FIntPoint D = PreviewLayoutSpec->DesignSize;
		if (D.X > 0 && D.Y > 0)
		{
			SourceDesign = D;
		}
	}

	const FString JsonForLog = Viewport != FIntPoint::ZeroValue
		? AutoUI_InjectPreviewViewportIntoLayoutJson(CachedLayoutJsonBody, Viewport, SourceDesign)
		: CachedLayoutJsonBody;

	const FString FullText = CachedLogHeaderPrefix.IsEmpty()
		? JsonForLog
		: CachedLogHeaderPrefix + JsonForLog;

	LogTextBox->SetText(FText::FromString(FullText));
}

void SAutoUITab::SetLayoutTexture(UTexture2D* Texture)
{
	ClearMathMatteResources();
	LastAiMatteBgra.Reset();
	LastAiMatteW = 0;
	LastAiMatteH = 0;
	LastMattePngSavedPath.Reset();
	LayoutTexture = Texture;
	ApplyOrClearIconMarkers(TOptional<FAutoUILayoutSpec>());
	RefreshPreview();
}

void SAutoUITab::ClearMathMatteResources()
{
	bShowingMathMatte = false;
	MathMatteTexture.Reset();
}

void SAutoUITab::SyncPreviewBrushDisplay()
{
	if (!LayoutTexture.IsValid())
	{
		PreviewBrush.SetResourceObject(nullptr);
		return;
	}

	UTexture2D* DisplayTex = LayoutTexture.Get();
	if (bShowingMathMatte && MathMatteTexture.IsValid())
	{
		DisplayTex = MathMatteTexture.Get();
	}

	PreviewBrush.SetResourceObject(DisplayTex);
	PreviewBrush.ImageSize = FVector2D(static_cast<float>(LayoutTexture->GetSizeX()), static_cast<float>(LayoutTexture->GetSizeY()));
}

void SAutoUITab::RefreshPreview()
{
	PreviewBrush = FSlateBrush();
	PreviewBrush.DrawAs = ESlateBrushDrawType::Image;
	PreviewBrush.Tiling = ESlateBrushTileType::NoTile;

	SyncPreviewBrushDisplay();

	if (PreviewImage.IsValid())
	{
		PreviewImage->Invalidate(EInvalidateWidgetReason::Paint);
	}

	if (PreviewInnerBox.IsValid())
	{
		PreviewInnerBox->Invalidate(EInvalidateWidgetReason::Layout);
	}

	LastPreviewAreaSize = FVector2D::ZeroVector;
	LastOuterPanelLocalSize = FVector2D::ZeroVector;
}

const FSlateBrush* SAutoUITab::GetPreviewBrush() const
{
	return LayoutTexture.IsValid() ? &PreviewBrush : FAppStyle::Get().GetBrush("Checkerboard");
}

bool SAutoUITab::AreTextureAssetsAcceptableForDrop(TArrayView<FAssetData> InAssets) const
{
	for (const FAssetData& Asset : InAssets)
	{
		if (Asset.IsValid() && Cast<UTexture2D>(Asset.GetAsset()) != nullptr)
		{
			return true;
		}
	}
	return false;
}

void SAutoUITab::OnTextureAssetsDropped(const FDragDropEvent&, TArrayView<FAssetData> InAssets)
{
	for (const FAssetData& Asset : InAssets)
	{
		if (UTexture2D* Tex = Cast<UTexture2D>(Asset.GetAsset()))
		{
			SetLayoutTexture(Tex);
			break;
		}
	}
}

void SAutoUITab::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	const FVector2D TabLocal = AllottedGeometry.GetLocalSize();
	if (TabLocal.X > 1.f && TabLocal.Y > 1.f)
	{
		const bool bTabResized =
			!FMath::IsNearlyEqual(TabLocal.X, LastOuterPanelLocalSize.X, 0.25f) ||
			!FMath::IsNearlyEqual(TabLocal.Y, LastOuterPanelLocalSize.Y, 0.25f);
		if (bTabResized)
		{
			LastOuterPanelLocalSize = TabLocal;
			LastPreviewAreaSize = FVector2D::ZeroVector;
			if (PreviewSizer.IsValid())
			{
				PreviewSizer->Invalidate(EInvalidateWidgetReason::Layout);
			}
		}
	}

	UTexture2D* Tex = LayoutTexture.Get();
	if (!Tex || !PreviewSizer.IsValid() || !PreviewInnerBox.IsValid() || !PreviewImage.IsValid())
	{
		return;
	}

	// 预览视口：与 SImage / 叠层共用的内层盒子几何（设计坐标 → 视口 的矩阵在此尺寸上计算）。
	FVector2D Viewport = PreviewInnerBox->GetCachedGeometry().GetLocalSize();
	if (Viewport.X <= 1.f || Viewport.Y <= 1.f)
	{
		Viewport = PreviewSizer->GetCachedGeometry().GetLocalSize();
	}
	if (Viewport.X <= 1.f || Viewport.Y <= 1.f)
	{
		return;
	}

	if ((Viewport - LastPreviewAreaSize).Size() < 0.5f)
	{
		return;
	}

	LastPreviewAreaSize = Viewport;

	const float TexW = static_cast<float>(Tex->GetSizeX());
	const float TexH = static_cast<float>(Tex->GetSizeY());
	if (TexW <= KINDA_SMALL_NUMBER || TexH <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	// 底图按视口非等比铺满；叠层用同一视口尺寸的 design→viewport 矩阵。
	PreviewBrush.ImageSize = Viewport;

	PreviewInnerBox->Invalidate(EInvalidateWidgetReason::Layout);
	PreviewImage->Invalidate(EInvalidateWidgetReason::Layout);
	PreviewImage->Invalidate(EInvalidateWidgetReason::Paint);
	if (IconOverlay.IsValid())
	{
		IconOverlay->Invalidate(EInvalidateWidgetReason::Layout);
		IconOverlay->Invalidate(EInvalidateWidgetReason::Paint);
	}

	UpdatePreviewViewportTransform();
	RefreshLogLayoutJsonWithViewport();
}

#undef LOCTEXT_NAMESPACE
