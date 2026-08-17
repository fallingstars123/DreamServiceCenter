// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoUIAiServiceSettings.h"

UAutoUIAiServiceSettings::UAutoUIAiServiceSettings()
{
	ServiceUrl = TEXT("https://api.openai.com/v1/chat/completions");
	ModelName = TEXT("gpt-4o-mini");
}

FName UAutoUIAiServiceSettings::GetCategoryName() const
{
	return TEXT("Plugins");
}

FName UAutoUIAiServiceSettings::GetSectionName() const
{
	return TEXT("Auto UI AI");
}
