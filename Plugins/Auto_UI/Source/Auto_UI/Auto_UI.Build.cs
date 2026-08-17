// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Auto_UI : ModuleRules
{
	public Auto_UI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// 避免新 .cpp 未并入 Unity 分块导致漏编（如 SAutoUIIconOverlay、AutoUILayoutBlockMerge）。
		bUseUnity = false;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"InputCore",
			"ApplicationCore",
			"UnrealEd",
			"EditorStyle",
			"EditorWidgets",
			"ToolMenus",
			"WorkspaceMenuStructure",
			"LevelEditor",
			"AssetRegistry",
			"DesktopPlatform",
			"Json",
			"JsonUtilities",
			"UMG",
			"UMGEditor",
			"AssetTools",
			"HTTP",
			"DeveloperSettings",
			"ImageCore",
			"ImageWrapper",
		});
	}
}
