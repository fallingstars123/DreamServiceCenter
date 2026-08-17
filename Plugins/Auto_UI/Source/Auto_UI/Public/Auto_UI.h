// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FSpawnTabArgs;
class SDockTab;

class FAuto_UIModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterMenus();
	void OpenAutoUIPanelTab();
	TSharedRef<SDockTab> SpawnAutoUIPanelTab(const FSpawnTabArgs& Args);

	static const FName AutoUIPanelTabName;
};
