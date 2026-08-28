// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplatActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianSplatActor() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_AGaussianSplatActor(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_AGaussianSplatActor(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatComponent(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatSelectionBoxComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class AGaussianSplatActor ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AGaussianSplatActor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Simple actor for placing Gaussian Splats in the level.\n * Drag and drop a Gaussian Splat Asset from the Content Browser to spawn this actor.\n */" },
#endif
		{ "IncludePath", "GaussianSplatActor.h" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple actor for placing Gaussian Splats in the level.\nDrag and drop a Gaussian Splat Asset from the Content Browser to spawn this actor." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GaussianSplatComponent_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The Gaussian Splat component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The Gaussian Splat component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableCullSelectionBoxes_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enable all cull boxes. Splats inside any cull box are hidden. */" },
#endif
		{ "DisplayName", "Enable Cull Selection Boxes" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable all cull boxes. Splats inside any cull box are hidden." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableKeepSelectionBoxes_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enable all keep boxes. Their union is retained; cull boxes can remove points inside it. */" },
#endif
		{ "DisplayName", "Enable Keep Selection Boxes" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable all keep boxes. Their union is retained; cull boxes can remove points inside it." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionBoxOverlapPriority_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Choose which operation wins where cull and keep boxes overlap. */" },
#endif
		{ "DisplayName", "Overlap Priority" },
		{ "EditCondition", "bEnableCullSelectionBoxes && bEnableKeepSelectionBoxes" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Choose which operation wins where cull and keep boxes overlap." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CullSelectionBoxes_Inner_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
		{ "DisplayName", "Cull Selection Boxes" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
		{ "NoElementDuplicate", "" },
		{ "TitleProperty", "SelectionBoxName" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CullSelectionBoxes_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
		{ "DisplayName", "Cull Selection Boxes" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
		{ "NoElementDuplicate", "" },
		{ "TitleProperty", "SelectionBoxName" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KeepSelectionBoxes_Inner_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
		{ "DisplayName", "Keep Selection Boxes" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
		{ "NoElementDuplicate", "" },
		{ "TitleProperty", "SelectionBoxName" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KeepSelectionBoxes_MetaData[] = {
		{ "Category", "Gaussian Splatting|Selection Boxes" },
		{ "DisplayName", "Keep Selection Boxes" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GaussianSplatActor.h" },
		{ "NoElementDuplicate", "" },
		{ "TitleProperty", "SelectionBoxName" },
	};
#endif // WITH_METADATA

// ********** Begin Class AGaussianSplatActor constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GaussianSplatComponent;
	static void NewProp_bEnableCullSelectionBoxes_SetBit(void* Obj)
	{
		((AGaussianSplatActor*)Obj)->bEnableCullSelectionBoxes = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableCullSelectionBoxes;
	static void NewProp_bEnableKeepSelectionBoxes_SetBit(void* Obj)
	{
		((AGaussianSplatActor*)Obj)->bEnableKeepSelectionBoxes = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableKeepSelectionBoxes;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionBoxOverlapPriority_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SelectionBoxOverlapPriority;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CullSelectionBoxes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CullSelectionBoxes;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_KeepSelectionBoxes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_KeepSelectionBoxes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AGaussianSplatActor constinit property declarations ************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGaussianSplatActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AGaussianSplatActor Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_GaussianSplatComponent = { "GaussianSplatComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(AGaussianSplatActor, GaussianSplatComponent), Z_Construct_UClass_UGaussianSplatComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GaussianSplatComponent_MetaData), NewProp_GaussianSplatComponent_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEnableCullSelectionBoxes = { "bEnableCullSelectionBoxes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(AGaussianSplatActor), &UHT_STATICS::NewProp_bEnableCullSelectionBoxes_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableCullSelectionBoxes_MetaData), NewProp_bEnableCullSelectionBoxes_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEnableKeepSelectionBoxes = { "bEnableKeepSelectionBoxes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(AGaussianSplatActor), &UHT_STATICS::NewProp_bEnableKeepSelectionBoxes_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableKeepSelectionBoxes_MetaData), NewProp_bEnableKeepSelectionBoxes_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SelectionBoxOverlapPriority_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_SelectionBoxOverlapPriority = { "SelectionBoxOverlapPriority", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(AGaussianSplatActor, SelectionBoxOverlapPriority), Z_Construct_UEnum_NanoGS_EGaussianSplatSelectionBoxMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionBoxOverlapPriority_MetaData), NewProp_SelectionBoxOverlapPriority_MetaData) }; // e718b1955c66ce57e4f662dfeb93895c7c857d7b
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CullSelectionBoxes_Inner = { "CullSelectionBoxes", nullptr, (EPropertyFlags)0x0106000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UGaussianSplatSelectionBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CullSelectionBoxes_Inner_MetaData), NewProp_CullSelectionBoxes_Inner_MetaData) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_CullSelectionBoxes = { "CullSelectionBoxes", nullptr, (EPropertyFlags)0x0144008000000809, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(AGaussianSplatActor, CullSelectionBoxes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CullSelectionBoxes_MetaData), NewProp_CullSelectionBoxes_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_KeepSelectionBoxes_Inner = { "KeepSelectionBoxes", nullptr, (EPropertyFlags)0x0106000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UGaussianSplatSelectionBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KeepSelectionBoxes_Inner_MetaData), NewProp_KeepSelectionBoxes_Inner_MetaData) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_KeepSelectionBoxes = { "KeepSelectionBoxes", nullptr, (EPropertyFlags)0x0144008000000809, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(AGaussianSplatActor, KeepSelectionBoxes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KeepSelectionBoxes_MetaData), NewProp_KeepSelectionBoxes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GaussianSplatComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEnableCullSelectionBoxes,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEnableKeepSelectionBoxes,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionBoxOverlapPriority_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionBoxOverlapPriority,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CullSelectionBoxes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CullSelectionBoxes,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_KeepSelectionBoxes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_KeepSelectionBoxes,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AGaussianSplatActor Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AGaussianSplatActor,
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
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_AGaussianSplatActor;
UClass* Z_Construct_UClass_AGaussianSplatActor(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AGaussianSplatActor;
		if (!Z_Registration_Info_UClass_AGaussianSplatActor.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("GaussianSplatActor"),
				Z_Registration_Info_UClass_AGaussianSplatActor.InnerSingleton,
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
		return Z_Registration_Info_UClass_AGaussianSplatActor.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AGaussianSplatActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGaussianSplatActor.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AGaussianSplatActor.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AGaussianSplatActor);
AGaussianSplatActor::~AGaussianSplatActor() {}
// ********** End Class AGaussianSplatActor ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatActor_h__Script_NanoGS_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGaussianSplatActor, TEXT("AGaussianSplatActor"), &Z_Registration_Info_UClass_AGaussianSplatActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGaussianSplatActor), 2812931841U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatActor_h__Script_NanoGS_32d9d335a2c9b01561065476ed3f78fae4d7ff6e{
	TEXT("/Script/NanoGS"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
