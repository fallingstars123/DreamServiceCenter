// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNanoGSEditor_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_NanoGSEditor;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_NanoGSEditor(ETypeConstructPhase)
	{
		if (!Z_Registration_Info_UPackage__Script_NanoGSEditor.OuterSingleton)
		{
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/NanoGSEditor",
			nullptr,
			0,
			PKG_CompiledIn | 0x00000040,
			0x6691E31D,
			0xDFE0E3EF,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_NanoGSEditor.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_NanoGSEditor.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_NanoGSEditor(Z_Construct_UPackage__Script_NanoGSEditor, TEXT("/Script/NanoGSEditor"), Z_Registration_Info_UPackage__Script_NanoGSEditor, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x6691E31D, 0xDFE0E3EF));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
