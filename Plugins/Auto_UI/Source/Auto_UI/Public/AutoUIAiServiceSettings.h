// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AutoUIAiServiceSettings.generated.h"

/**
 * AI 识图服务配置（Editor 每用户/每项目配置，勿将含 API Key 的 ini 提交到版本库）。
 * 请求体为 OpenAI 兼容的 chat/completions（多模态：text + image_url data URL）。
 */
UCLASS(Config = EditorPerProjectUserSettings, DefaultConfig, meta = (DisplayName = "Auto UI AI 服务"))
class UAutoUIAiServiceSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UAutoUIAiServiceSettings();

	/** 完整 HTTP 端点，例如 https://api.openai.com/v1/chat/completions */
	UPROPERTY(Config, EditAnywhere, Category = "Connection", meta = (DisplayName = "备用 REST 服务 URL"))
	FString ServiceUrl;

	/** 模型名，例如 gpt-4o-mini */
	UPROPERTY(Config, EditAnywhere, Category = "Connection", meta = (DisplayName = "备用 REST 模型名"))
	FString ModelName;

	/** API Key（Authorization: Bearer）。为空时自动读取 OPENAI_API_KEY 环境变量。 */
	UPROPERTY(Config, EditAnywhere, Category = "Connection", meta = (DisplayName = "备用 REST API Key", PasswordField = true))
	FString ApiKey;

	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;
};
