// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNanoGS_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_NanoGS;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase)
	{
		if (!Z_Registration_Info_UPackage__Script_NanoGS.OuterSingleton)
		{
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/NanoGS",
			nullptr,
			0,
			PKG_CompiledIn | 0x00000000,
			0x74BD6648,
			0xCFA7F2F6,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_NanoGS.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_NanoGS.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_NanoGS(Z_Construct_UPackage__Script_NanoGS, TEXT("/Script/NanoGS"), Z_Registration_Info_UPackage__Script_NanoGS, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x74BD6648, 0xCFA7F2F6));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
