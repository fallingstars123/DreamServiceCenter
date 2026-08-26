// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplatSelectionBoxComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianSplatSelectionBoxComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatSelectionBoxComponent(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatSelectionBoxComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EGaussianSplatSelectionBoxMode ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode_Statics
template<> NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianSplatSelectionBoxMode>()
{
	return Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Cull.DisplayName", "\xe5\x89\x94\xe9\x99\xa4" },
		{ "Cull.Name", "EGaussianSplatSelectionBoxMode::Cull" },
		{ "Keep.DisplayName", "\xe4\xbf\x9d\xe7\x95\x99" },
		{ "Keep.Name", "EGaussianSplatSelectionBoxMode::Keep" },
		{ "ModuleRelativePath", "Public/GaussianSplatSelectionBoxComponent.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSplatSelectionBoxMode::Cull", (int64)EGaussianSplatSelectionBoxMode::Cull },
		{ "EGaussianSplatSelectionBoxMode::Keep", (int64)EGaussianSplatSelectionBoxMode::Keep },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	"EGaussianSplatSelectionBoxMode",
	"EGaussianSplatSelectionBoxMode",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EGaussianSplatSelectionBoxMode;
UEnum* Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EGaussianSplatSelectionBoxMode.OuterSingleton)
		{
			ZRIE_EGaussianSplatSelectionBoxMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("EGaussianSplatSelectionBoxMode"));
		}
		return ZRIE_EGaussianSplatSelectionBoxMode.OuterSingleton;
	}
	if (!ZRIE_EGaussianSplatSelectionBoxMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EGaussianSplatSelectionBoxMode.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EGaussianSplatSelectionBoxMode.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EGaussianSplatSelectionBoxMode **********************************************

// ********** Begin Class UGaussianSplatSelectionBoxComponent **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UGaussianSplatSelectionBoxComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Rendering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * An editor-visible box used to mask Gaussian splats. The component never\n * collides and is hidden during play; only its transform and extent are used.\n */" },
#endif
		{ "HideCategories", "Object Gaussian Splatting Transform Shape HLOD Collision Rendering Mobile Mobility Physics Navigation LOD Lighting TextureStreaming Activation Components|Activation Cooking Tags AssetUserData Replication ComponentTick Events Input Object LOD Lighting TextureStreaming Object LOD Lighting TextureStreaming Activation Components|Activation Trigger VirtualTexture" },
		{ "IncludePath", "GaussianSplatSelectionBoxComponent.h" },
		{ "ModuleRelativePath", "Public/GaussianSplatSelectionBoxComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An editor-visible box used to mask Gaussian splats. The component never\ncollides and is hidden during play; only its transform and extent are used." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionBoxName_MetaData[] = {
		{ "Category", "Selection Box" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** User-facing label shown for this entry in the actor details panel. */" },
#endif
		{ "DisplayName", "Name" },
		{ "ModuleRelativePath", "Public/GaussianSplatSelectionBoxComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "User-facing label shown for this entry in the actor details panel." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionBoxTransform_MetaData[] = {
		{ "Category", "Selection Box" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Transform relative to the Gaussian Splat actor. Synchronized with the viewport box. */" },
#endif
		{ "DisplayName", "Transform" },
		{ "ModuleRelativePath", "Public/GaussianSplatSelectionBoxComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Transform relative to the Gaussian Splat actor. Synchronized with the viewport box." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionMode_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Internal mode; the owning array decides whether this is a cull or keep box. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatSelectionBoxComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Internal mode; the owning array decides whether this is a cull or keep box." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UGaussianSplatSelectionBoxComponent constinit property declarations ******
	static const UECodeGen_Private::FNamePropertyParams NewProp_SelectionBoxName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SelectionBoxTransform;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SelectionMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UGaussianSplatSelectionBoxComponent constinit property declarations ********
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplatSelectionBoxComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UGaussianSplatSelectionBoxComponent Property Definitions *****************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SelectionBoxName = { "SelectionBoxName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatSelectionBoxComponent, SelectionBoxName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionBoxName_MetaData), NewProp_SelectionBoxName_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SelectionBoxTransform = { "SelectionBoxTransform", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatSelectionBoxComponent, SelectionBoxTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionBoxTransform_MetaData), NewProp_SelectionBoxTransform_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SelectionMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_SelectionMode = { "SelectionMode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatSelectionBoxComponent, SelectionMode), Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionMode_MetaData), NewProp_SelectionMode_MetaData) }; // c9d3f1e12771a1e231be6c4855bc887ffe27d5b4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionBoxName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionBoxTransform,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionMode,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UGaussianSplatSelectionBoxComponent Property Definitions *******************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UBoxComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UGaussianSplatSelectionBoxComponent,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x00B010A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent;
UClass* Z_Construct_UClass_UGaussianSplatSelectionBoxComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UGaussianSplatSelectionBoxComponent;
		if (!Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("GaussianSplatSelectionBoxComponent"),
				Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent.InnerSingleton,
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
		return Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UGaussianSplatSelectionBoxComponent);
UGaussianSplatSelectionBoxComponent::~UGaussianSplatSelectionBoxComponent() {}
// ********** End Class UGaussianSplatSelectionBoxComponent ****************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h__Script_NanoGS_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode, TEXT("EGaussianSplatSelectionBoxMode"), &ZRIE_EGaussianSplatSelectionBoxMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3386110433U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplatSelectionBoxComponent, TEXT("UGaussianSplatSelectionBoxComponent"), &Z_Registration_Info_UClass_UGaussianSplatSelectionBoxComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplatSelectionBoxComponent), 692164972U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h__Script_NanoGS_e356bda07f403133ac812fe6255d3c91a4163557{
	TEXT("/Script/NanoGS"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
