// Copyright Epic Games, Inc. All Rights Reserved.

#include "Auto_UI.h"

#include "Editor.h"
#include "Framework/Docking/TabManager.h"
#include "HttpModule.h"
#include "LevelEditor.h"
#include "Modules/ModuleManager.h"
#include "SAutoUITab.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FAuto_UIModule"

const FName FAuto_UIModule::AutoUIPanelTabName(TEXT("AutoUI_Panel_v1"));

void FAuto_UIModule::StartupModule()
{
	FModuleManager::Get().LoadModuleChecked(TEXT("HTTP"));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		AutoUIPanelTabName,
		FOnSpawnTab::CreateRaw(this, &FAuto_UIModule::SpawnAutoUIPanelTab))
		.SetDisplayName(LOCTEXT("AutoUITabTitle", "Auto UI"))
		.SetTooltipText(LOCTEXT("AutoUITabTooltip", "布局图预览与 JSON 校验"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetMenuType(ETabSpawnerMenuType::Enabled);

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAuto_UIModule::RegisterMenus));
}

void FAuto_UIModule::ShutdownModule()
{
	if (GEditor)
	{
		UToolMenus::UnregisterOwner(GEditor);
	}

	if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AutoUIPanelTabName);
	}
}

void FAuto_UIModule::OpenAutoUIPanelTab()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(AutoUIPanelTabName));
}

void FAuto_UIModule::RegisterMenus()
{
	if (!GEditor)
	{
		return;
	}

	FToolMenuOwnerScoped OwnerScoped(GEditor);

	UToolMenu* const Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	FToolMenuSection& Section = Menu->FindOrAddSection("AutoUISection");
	Section.AddMenuEntry(
		"OpenAutoUIPanelTab",
		LOCTEXT("OpenAutoUI", "Auto UI"),
		LOCTEXT("OpenAutoUITip", "打开 Auto UI 面板"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports"),
		FUIAction(FExecuteAction::CreateRaw(this, &FAuto_UIModule::OpenAutoUIPanelTab)));
}

TSharedRef<SDockTab> FAuto_UIModule::SpawnAutoUIPanelTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(LOCTEXT("DockTabLabel", "Auto UI"))
		[
			SNew(SAutoUITab)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAuto_UIModule, Auto_UI)
