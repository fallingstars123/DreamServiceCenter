// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AutoUIAiServiceSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeAutoUIAiServiceSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_Auto_UI(ETypeConstructPhase);
AUTO_UI_API UClass* Z_Construct_UClass_UAutoUIAiServiceSettings(ETypeConstructPhase);
AUTO_UI_API UClass* Z_Construct_UClass_UAutoUIAiServiceSettings(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UAutoUIAiServiceSettings *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UAutoUIAiServiceSettings_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * AI \xe8\xaf\x86\xe5\x9b\xbe\xe6\x9c\x8d\xe5\x8a\xa1\xe9\x85\x8d\xe7\xbd\xae\xef\xbc\x88""Editor \xe6\xaf\x8f\xe7\x94\xa8\xe6\x88\xb7/\xe6\xaf\x8f\xe9\xa1\xb9\xe7\x9b\xae\xe9\x85\x8d\xe7\xbd\xae\xef\xbc\x8c\xe5\x8b\xbf\xe5\xb0\x86\xe5\x90\xab API Key \xe7\x9a\x84 ini \xe6\x8f\x90\xe4\xba\xa4\xe5\x88\xb0\xe7\x89\x88\xe6\x9c\xac\xe5\xba\x93\xef\xbc\x89\xe3\x80\x82\n * \xe8\xaf\xb7\xe6\xb1\x82\xe4\xbd\x93\xe4\xb8\xba OpenAI \xe5\x85\xbc\xe5\xae\xb9\xe7\x9a\x84 chat/completions\xef\xbc\x88\xe5\xa4\x9a\xe6\xa8\xa1\xe6\x80\x81\xef\xbc\x9atext + image_url data URL\xef\xbc\x89\xe3\x80\x82\n */" },
#endif
		{ "DisplayName", "Auto UI AI \xe6\x9c\x8d\xe5\x8a\xa1" },
		{ "IncludePath", "AutoUIAiServiceSettings.h" },
		{ "ModuleRelativePath", "Public/AutoUIAiServiceSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI \xe8\xaf\x86\xe5\x9b\xbe\xe6\x9c\x8d\xe5\x8a\xa1\xe9\x85\x8d\xe7\xbd\xae\xef\xbc\x88""Editor \xe6\xaf\x8f\xe7\x94\xa8\xe6\x88\xb7/\xe6\xaf\x8f\xe9\xa1\xb9\xe7\x9b\xae\xe9\x85\x8d\xe7\xbd\xae\xef\xbc\x8c\xe5\x8b\xbf\xe5\xb0\x86\xe5\x90\xab API Key \xe7\x9a\x84 ini \xe6\x8f\x90\xe4\xba\xa4\xe5\x88\xb0\xe7\x89\x88\xe6\x9c\xac\xe5\xba\x93\xef\xbc\x89\xe3\x80\x82\n\xe8\xaf\xb7\xe6\xb1\x82\xe4\xbd\x93\xe4\xb8\xba OpenAI \xe5\x85\xbc\xe5\xae\xb9\xe7\x9a\x84 chat/completions\xef\xbc\x88\xe5\xa4\x9a\xe6\xa8\xa1\xe6\x80\x81\xef\xbc\x9atext + image_url data URL\xef\xbc\x89\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServiceUrl_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xae\x8c\xe6\x95\xb4 HTTP \xe7\xab\xaf\xe7\x82\xb9\xef\xbc\x8c\xe4\xbe\x8b\xe5\xa6\x82 https://api.openai.com/v1/chat/completions */" },
#endif
		{ "DisplayName", "\xe6\x9c\x8d\xe5\x8a\xa1 URL" },
		{ "ModuleRelativePath", "Public/AutoUIAiServiceSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xae\x8c\xe6\x95\xb4 HTTP \xe7\xab\xaf\xe7\x82\xb9\xef\xbc\x8c\xe4\xbe\x8b\xe5\xa6\x82 https://api.openai.com/v1/chat/completions" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelName_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xa8\xa1\xe5\x9e\x8b\xe5\x90\x8d\xef\xbc\x8c\xe4\xbe\x8b\xe5\xa6\x82 gpt-4o-mini */" },
#endif
		{ "DisplayName", "\xe6\xa8\xa1\xe5\x9e\x8b\xe5\x90\x8d" },
		{ "ModuleRelativePath", "Public/AutoUIAiServiceSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xa8\xa1\xe5\x9e\x8b\xe5\x90\x8d\xef\xbc\x8c\xe4\xbe\x8b\xe5\xa6\x82 gpt-4o-mini" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApiKey_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** API Key\xef\xbc\x88""Authorization: Bearer\xef\xbc\x89 */" },
#endif
		{ "DisplayName", "API Key" },
		{ "ModuleRelativePath", "Public/AutoUIAiServiceSettings.h" },
		{ "PasswordField", "TRUE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "API Key\xef\xbc\x88""Authorization: Bearer\xef\xbc\x89" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UAutoUIAiServiceSettings constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServiceUrl;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ApiKey;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UAutoUIAiServiceSettings constinit property declarations *******************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAutoUIAiServiceSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UAutoUIAiServiceSettings Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ServiceUrl = { "ServiceUrl", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UAutoUIAiServiceSettings, ServiceUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServiceUrl_MetaData), NewProp_ServiceUrl_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ModelName = { "ModelName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UAutoUIAiServiceSettings, ModelName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelName_MetaData), NewProp_ModelName_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ApiKey = { "ApiKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UAutoUIAiServiceSettings, ApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApiKey_MetaData), NewProp_ApiKey_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ServiceUrl,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ModelName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ApiKey,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UAutoUIAiServiceSettings Property Definitions ******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UDeveloperSettings,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_Auto_UI,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UAutoUIAiServiceSettings,
	"EditorPerProjectUserSettings",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x000000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UAutoUIAiServiceSettings;
UClass* Z_Construct_UClass_UAutoUIAiServiceSettings(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UAutoUIAiServiceSettings;
		if (!Z_Registration_Info_UClass_UAutoUIAiServiceSettings.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("AutoUIAiServiceSettings"),
				Z_Registration_Info_UClass_UAutoUIAiServiceSettings.InnerSingleton,
				nullptr,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_UAutoUIAiServiceSettings.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UAutoUIAiServiceSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAutoUIAiServiceSettings.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UAutoUIAiServiceSettings.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UAutoUIAiServiceSettings);
UAutoUIAiServiceSettings::~UAutoUIAiServiceSettings() {}
// ********** End Class UAutoUIAiServiceSettings ***************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_Auto_UI_Source_Auto_UI_Public_AutoUIAiServiceSettings_h__Script_Auto_UI_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAutoUIAiServiceSettings, TEXT("UAutoUIAiServiceSettings"), &Z_Registration_Info_UClass_UAutoUIAiServiceSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAutoUIAiServiceSettings), 2076928469U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_Auto_UI_Source_Auto_UI_Public_AutoUIAiServiceSettings_h__Script_Auto_UI_9d83dd53038831cb6ccc34a0335598028a86b3cb{
	TEXT("/Script/Auto_UI"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
