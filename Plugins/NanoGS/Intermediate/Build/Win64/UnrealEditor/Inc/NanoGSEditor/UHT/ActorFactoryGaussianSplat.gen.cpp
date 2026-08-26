// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ActorFactoryGaussianSplat.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeActorFactoryGaussianSplat() {}

// ********** Begin Cross Module References ********************************************************
UNREALED_API UClass* Z_Construct_UClass_UActorFactory(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGSEditor(ETypeConstructPhase);
NANOGSEDITOR_API UClass* Z_Construct_UClass_UActorFactoryGaussianSplat(ETypeConstructPhase);
NANOGSEDITOR_API UClass* Z_Construct_UClass_UActorFactoryGaussianSplat(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UActorFactoryGaussianSplat ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UActorFactoryGaussianSplat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Actor factory for creating Gaussian Splat Actors from Gaussian Splat Assets.\n * Enables drag-and-drop from Content Browser into the level.\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "ActorFactoryGaussianSplat.h" },
		{ "ModuleRelativePath", "Private/ActorFactoryGaussianSplat.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor factory for creating Gaussian Splat Actors from Gaussian Splat Assets.\nEnables drag-and-drop from Content Browser into the level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UActorFactoryGaussianSplat constinit property declarations ***************
// ********** End Class UActorFactoryGaussianSplat constinit property declarations *****************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActorFactoryGaussianSplat>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorFactory,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGSEditor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UActorFactoryGaussianSplat,
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
	0x000830ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UActorFactoryGaussianSplat;
UClass* Z_Construct_UClass_UActorFactoryGaussianSplat(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UActorFactoryGaussianSplat;
		if (!Z_Registration_Info_UClass_UActorFactoryGaussianSplat.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ActorFactoryGaussianSplat"),
				Z_Registration_Info_UClass_UActorFactoryGaussianSplat.InnerSingleton,
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
		return Z_Registration_Info_UClass_UActorFactoryGaussianSplat.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UActorFactoryGaussianSplat.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UActorFactoryGaussianSplat.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UActorFactoryGaussianSplat.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UActorFactoryGaussianSplat);
UActorFactoryGaussianSplat::~UActorFactoryGaussianSplat() {}
// ********** End Class UActorFactoryGaussianSplat *************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGSEditor_Private_ActorFactoryGaussianSplat_h__Script_NanoGSEditor_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UActorFactoryGaussianSplat, TEXT("UActorFactoryGaussianSplat"), &Z_Registration_Info_UClass_UActorFactoryGaussianSplat, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UActorFactoryGaussianSplat), 36887702U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGSEditor_Private_ActorFactoryGaussianSplat_h__Script_NanoGSEditor_b8e939e219497543c65202c8f2050ee48e2f4d11{
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
