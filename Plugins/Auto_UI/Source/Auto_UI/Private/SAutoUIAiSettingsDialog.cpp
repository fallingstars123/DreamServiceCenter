// Copyright Epic Games, Inc. All Rights Reserved.

#include "SAutoUIAiSettingsDialog.h"

#include "AutoUIAiServiceSettings.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/AppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SWindow.h"

#define LOCTEXT_NAMESPACE "SAutoUIAiSettingsDialog"

void SAutoUIAiSettingsDialog::Construct(const FArguments& InArgs)
{
	const UAutoUIAiServiceSettings* Defaults = GetDefault<UAutoUIAiServiceSettings>();

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.LightGroupBorder"))
		.Padding(12.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 0.f, 0.f, 8.f)
			[
				SAssignNew(HelpText, SMultiLineEditableTextBox)
				.IsReadOnly(true)
				.AutoWrapText(true)
				.Text(LOCTEXT(
					"Help",
					"当前默认自动使用本机已登录的 Codex CLI。"
					"无需填写 URL、模型或 API Key，也不会读取或保存 Codex 登录令牌。\n"
					"仅当环境变量 AUTO_UI_USE_REST=1 时，才使用下方 OpenAI Chat Completions 兼容 REST 配置；API Key 留空时自动读取 OPENAI_API_KEY。\n"
					"手填的 Key 仍会保存在本机 Editor 用户设置，请勿将相关 ini 提交到 Git。\n"
					"• 主面板「用 AI 分析布局图」将按当前抠背景参数生成透明底 PNG 后发往该接口（非原图）。"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 4.f)
			[
				SNew(STextBlock).Text(LOCTEXT("LblUrl", "备用 REST 服务 URL"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(UrlEditor, SEditableTextBox)
				.Text(FText::FromString(Defaults->ServiceUrl))
				.HintText(LOCTEXT("HintUrl", "https://.../v1/chat/completions"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f, 0.f, 4.f)
			[
				SNew(STextBlock).Text(LOCTEXT("LblModel", "备用 REST 模型名"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(ModelEditor, SEditableTextBox)
				.Text(FText::FromString(Defaults->ModelName))
				.HintText(LOCTEXT("HintModel", "gpt-4o-mini"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f, 0.f, 4.f)
			[
				SNew(STextBlock).Text(LOCTEXT("LblKey", "备用 REST API Key"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(ApiKeyEditor, SEditableTextBox)
				.Text(FText::FromString(Defaults->ApiKey))
				.HintText(LOCTEXT("HintKey", "留空则读取 OPENAI_API_KEY"))
				.IsPassword(true)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			.Padding(0.f, 16.f, 0.f, 0.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(4.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("Cancel", "取消"))
					.OnClicked(this, &SAutoUIAiSettingsDialog::OnCancelClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Save", "保存"))
					.OnClicked(this, &SAutoUIAiSettingsDialog::OnSaveClicked)
				]
			]
		]
	];
}

FReply SAutoUIAiSettingsDialog::OnSaveClicked()
{
	UAutoUIAiServiceSettings* Mutable = GetMutableDefault<UAutoUIAiServiceSettings>();
	if (UrlEditor.IsValid())
	{
		Mutable->ServiceUrl = UrlEditor->GetText().ToString().TrimStartAndEnd();
	}
	if (ModelEditor.IsValid())
	{
		Mutable->ModelName = ModelEditor->GetText().ToString().TrimStartAndEnd();
	}
	if (ApiKeyEditor.IsValid())
	{
		Mutable->ApiKey = ApiKeyEditor->GetText().ToString().TrimStartAndEnd();
	}
	Mutable->SaveConfig();

	if (const TSharedPtr<SWindow> Win = FSlateApplication::Get().FindWidgetWindow(AsShared()))
	{
		Win->RequestDestroyWindow();
	}

	return FReply::Handled();
}

FReply SAutoUIAiSettingsDialog::OnCancelClicked()
{
	if (const TSharedPtr<SWindow> Win = FSlateApplication::Get().FindWidgetWindow(AsShared()))
	{
		Win->RequestDestroyWindow();
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
