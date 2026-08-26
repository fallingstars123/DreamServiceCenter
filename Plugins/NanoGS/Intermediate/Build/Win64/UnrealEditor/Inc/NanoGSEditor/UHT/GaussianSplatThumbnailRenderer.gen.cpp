// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplatThumbnailRenderer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianSplatThumbnailRenderer() {}

// ********** Begin Cross Module References ********************************************************
UNREALED_API UClass* Z_Construct_UClass_UDefaultSizedThumbnailRenderer(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGSEditor(ETypeConstructPhase);
NANOGSEDITOR_API UClass* Z_Construct_UClass_UGaussianSplatThumbnailRenderer(ETypeConstructPhase);
NANOGSEDITOR_API UClass* Z_Construct_UClass_UGaussianSplatThumbnailRenderer(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UGaussianSplatThumbnailRenderer ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UGaussianSplatThumbnailRenderer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Draws the pre-baked thumbnail texture stored inside a UGaussianSplatAsset.\n */" },
#endif
		{ "IncludePath", "GaussianSplatThumbnailRenderer.h" },
		{ "ModuleRelativePath", "Private/GaussianSplatThumbnailRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Draws the pre-baked thumbnail texture stored inside a UGaussianSplatAsset." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UGaussianSplatThumbnailRenderer constinit property declarations **********
// ********** End Class UGaussianSplatThumbnailRenderer constinit property declarations ************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplatThumbnailRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UDefaultSizedThumbnailRenderer,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGSEditor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UGaussianSplatThumbnailRenderer,
	"Editor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer;
UClass* Z_Construct_UClass_UGaussianSplatThumbnailRenderer(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UGaussianSplatThumbnailRenderer;
		if (!Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("GaussianSplatThumbnailRenderer"),
				Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer.InnerSingleton,
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
		return Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer.OuterSingleton;
}
#undef UHT_STATICS
UGaussianSplatThumbnailRenderer::UGaussianSplatThumbnailRenderer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UGaussianSplatThumbnailRenderer);
UGaussianSplatThumbnailRenderer::~UGaussianSplatThumbnailRenderer() {}
// ********** End Class UGaussianSplatThumbnailRenderer ********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGSEditor_Private_GaussianSplatThumbnailRenderer_h__Script_NanoGSEditor_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplatThumbnailRenderer, TEXT("UGaussianSplatThumbnailRenderer"), &Z_Registration_Info_UClass_UGaussianSplatThumbnailRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplatThumbnailRenderer), 129036085U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGSEditor_Private_GaussianSplatThumbnailRenderer_h__Script_NanoGSEditor_d99ce8fdfa4aebb8a8dffff96aa36da3d6a34fda{
	TEXT("/Script/NanoGSEditor"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
