// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SEditableTextBox;
class SMultiLineEditableTextBox;

/** 模态子窗口：编辑 AI 服务 URL / 模型 / API Key 并保存到 UDeveloperSettings。 */
class SAutoUIAiSettingsDialog : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAutoUIAiSettingsDialog) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FReply OnSaveClicked();
	FReply OnCancelClicked();

	TSharedPtr<SEditableTextBox> UrlEditor;
	TSharedPtr<SEditableTextBox> ModelEditor;
	TSharedPtr<SEditableTextBox> ApiKeyEditor;
	TSharedPtr<SMultiLineEditableTextBox> HelpText;
};
