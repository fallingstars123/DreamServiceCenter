// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplatComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianSplatComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatComponent(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatAsset(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EGaussianSplatRenderMode **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode_Statics
template<> NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianSplatRenderMode>()
{
	return Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Gaussian.DisplayName", "Gaussian" },
		{ "Gaussian.Name", "EGaussianSplatRenderMode::Gaussian" },
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
		{ "PointCloud.DisplayName", "Point Cloud" },
		{ "PointCloud.Name", "EGaussianSplatRenderMode::PointCloud" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSplatRenderMode::Gaussian", (int64)EGaussianSplatRenderMode::Gaussian },
		{ "EGaussianSplatRenderMode::PointCloud", (int64)EGaussianSplatRenderMode::PointCloud },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	"EGaussianSplatRenderMode",
	"EGaussianSplatRenderMode",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EGaussianSplatRenderMode;
UEnum* Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EGaussianSplatRenderMode.OuterSingleton)
		{
			ZRIE_EGaussianSplatRenderMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("EGaussianSplatRenderMode"));
		}
		return ZRIE_EGaussianSplatRenderMode.OuterSingleton;
	}
	if (!ZRIE_EGaussianSplatRenderMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EGaussianSplatRenderMode.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EGaussianSplatRenderMode.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EGaussianSplatRenderMode ****************************************************

// ********** Begin Class UGaussianSplatComponent Function GetSplatAsset ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatComponent_GetSplatAsset_Statics
struct UHT_STATICS
{
	struct GaussianSplatComponent_eventGetSplatAsset_Parms
	{
		UGaussianSplatAsset* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the currently assigned asset */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the currently assigned asset" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetSplatAsset constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSplatAsset constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSplatAsset Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatComponent_eventGetSplatAsset_Parms, ReturnValue), Z_Construct_UClass_UGaussianSplatAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSplatAsset Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatComponent, nullptr, "GetSplatAsset", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatComponent_eventGetSplatAsset_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatComponent_eventGetSplatAsset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatComponent_GetSplatAsset(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatComponent::execGetSplatAsset)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UGaussianSplatAsset**)Z_Param__Result=P_THIS->GetSplatAsset();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatComponent Function GetSplatAsset *****************************

// ********** Begin Class UGaussianSplatComponent Function GetSplatCount ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatComponent_GetSplatCount_Statics
struct UHT_STATICS
{
	struct GaussianSplatComponent_eventGetSplatCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the number of splats being rendered */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the number of splats being rendered" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetSplatCount constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSplatCount constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSplatCount Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatComponent_eventGetSplatCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSplatCount Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatComponent, nullptr, "GetSplatCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatComponent_eventGetSplatCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatComponent_eventGetSplatCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatComponent_GetSplatCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatComponent::execGetSplatCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetSplatCount();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatComponent Function GetSplatCount *****************************

// ********** Begin Class UGaussianSplatComponent Function SetSplatAsset ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatComponent_SetSplatAsset_Statics
struct UHT_STATICS
{
	struct GaussianSplatComponent_eventSetSplatAsset_Parms
	{
		UGaussianSplatAsset* NewAsset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the Gaussian Splat asset to render */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the Gaussian Splat asset to render" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetSplatAsset constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NewAsset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetSplatAsset constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetSplatAsset Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NewAsset = { "NewAsset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatComponent_eventSetSplatAsset_Parms, NewAsset), Z_Construct_UClass_UGaussianSplatAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewAsset,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetSplatAsset Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatComponent, nullptr, "SetSplatAsset", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatComponent_eventSetSplatAsset_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatComponent_eventSetSplatAsset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatComponent_SetSplatAsset(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatComponent::execSetSplatAsset)
{
	P_GET_OBJECT(UGaussianSplatAsset,Z_Param_NewAsset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSplatAsset(Z_Param_NewAsset);
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatComponent Function SetSplatAsset *****************************

// ********** Begin Class UGaussianSplatComponent **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UGaussianSplatComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Rendering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Component for rendering Gaussian Splatting assets in the scene\n */" },
#endif
		{ "HideCategories", "Collision Physics Navigation Mobility VirtualTexture Trigger" },
		{ "IncludePath", "GaussianSplatComponent.h" },
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component for rendering Gaussian Splatting assets in the scene" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplatAsset_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The Gaussian Splat asset to render */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The Gaussian Splat asset to render" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SHOrder_MetaData[] = {
		{ "Category", "Gaussian Splatting|Quality" },
		{ "ClampMax", "3" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spherical Harmonic order to use for rendering (0-3). Higher = more color detail but slower. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spherical Harmonic order to use for rendering (0-3). Higher = more color detail but slower." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SortEveryNthFrame_MetaData[] = {
		{ "Category", "Gaussian Splatting|Performance" },
		{ "ClampMax", "10" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sort splats every N frames. 1 = every frame. Higher values reduce GPU cost but may cause artifacts during fast camera movement. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sort splats every N frames. 1 = every frame. Higher values reduce GPU cost but may cause artifacts during fast camera movement." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpacityScale_MetaData[] = {
		{ "Category", "Gaussian Splatting|Rendering" },
		{ "ClampMax", "2.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Global opacity multiplier */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Global opacity multiplier" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplatScale_MetaData[] = {
		{ "Category", "Gaussian Splatting|Rendering" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scale multiplier for splat sizes */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scale multiplier for splat sizes" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RenderMode_MetaData[] = {
		{ "Category", "Gaussian Splatting|Rendering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rendering style. Point Cloud draws fixed-size screen-space circular points. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rendering style. Point Cloud draws fixed-size screen-space circular points." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PointSize_MetaData[] = {
		{ "Category", "Gaussian Splatting|Rendering" },
		{ "ClampMax", "64.0" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Point diameter in screen pixels when Render Mode is Point Cloud */" },
#endif
		{ "EditCondition", "RenderMode == EGaussianSplatRenderMode::PointCloud" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Point diameter in screen pixels when Render Mode is Point Cloud" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableFrustumCulling_MetaData[] = {
		{ "Category", "Gaussian Splatting|Performance" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enable frustum culling for better performance */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable frustum culling for better performance" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LODErrorThreshold_MetaData[] = {
		{ "Category", "Gaussian Splatting|Performance" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.001" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Projected error threshold for LOD selection (resolution-independent, like Nanite).\n\x09 *  Lower values = more conservative (keep detail longer, less LOD savings)\n\x09 *  Higher values = more aggressive (switch to LOD sooner, better performance)\n\x09 *  Uses projection-space units. ~0.03 \xe2\x89\x88 32 pixels at 1080p with 90\xc2\xb0 FOV. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Projected error threshold for LOD selection (resolution-independent, like Nanite).\nLower values = more conservative (keep detail longer, less LOD savings)\nHigher values = more aggressive (switch to LOD sooner, better performance)\nUses projection-space units. ~0.03 \xe2\x89\x88 32 pixels at 1080p with 90\xc2\xb0 FOV." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UGaussianSplatComponent constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SplatAsset;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SHOrder;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SortEveryNthFrame;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OpacityScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SplatScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_RenderMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_RenderMode;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PointSize;
	static void NewProp_bEnableFrustumCulling_SetBit(void* Obj)
	{
		((UGaussianSplatComponent*)Obj)->bEnableFrustumCulling = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableFrustumCulling;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LODErrorThreshold;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UGaussianSplatComponent constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetSplatAsset"), .Pointer = &UGaussianSplatComponent::execGetSplatAsset },
		{ .NameUTF8 = UTF8TEXT("GetSplatCount"), .Pointer = &UGaussianSplatComponent::execGetSplatCount },
		{ .NameUTF8 = UTF8TEXT("SetSplatAsset"), .Pointer = &UGaussianSplatComponent::execSetSplatAsset },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGaussianSplatComponent_GetSplatAsset, "GetSplatAsset" }, // ecf6e28b5f4e98ebb68ec7156d6b35179f7ff995
		{ &Z_Construct_UFunction_UGaussianSplatComponent_GetSplatCount, "GetSplatCount" }, // 9dcb8977539f254e1d8096858ac9c93f8c0b824f
		{ &Z_Construct_UFunction_UGaussianSplatComponent_SetSplatAsset, "SetSplatAsset" }, // 7a82ca3e95be212e25cbf8e7bcfaca2c69fcd2ab
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplatComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UGaussianSplatComponent Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SplatAsset = { "SplatAsset", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, SplatAsset), Z_Construct_UClass_UGaussianSplatAsset, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplatAsset_MetaData), NewProp_SplatAsset_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SHOrder = { "SHOrder", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, SHOrder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SHOrder_MetaData), NewProp_SHOrder_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SortEveryNthFrame = { "SortEveryNthFrame", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, SortEveryNthFrame), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SortEveryNthFrame_MetaData), NewProp_SortEveryNthFrame_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_OpacityScale = { "OpacityScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, OpacityScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpacityScale_MetaData), NewProp_OpacityScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SplatScale = { "SplatScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, SplatScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplatScale_MetaData), NewProp_SplatScale_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_RenderMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_RenderMode = { "RenderMode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, RenderMode), Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RenderMode_MetaData), NewProp_RenderMode_MetaData) }; // af78e18f9d7813898b722e88ae714106ab33f1c7
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_PointSize = { "PointSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, PointSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointSize_MetaData), NewProp_PointSize_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEnableFrustumCulling = { "bEnableFrustumCulling", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UGaussianSplatComponent), &UHT_STATICS::NewProp_bEnableFrustumCulling_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableFrustumCulling_MetaData), NewProp_bEnableFrustumCulling_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LODErrorThreshold = { "LODErrorThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatComponent, LODErrorThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LODErrorThreshold_MetaData), NewProp_LODErrorThreshold_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SplatAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SHOrder,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SortEveryNthFrame,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpacityScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SplatScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RenderMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RenderMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PointSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEnableFrustumCulling,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LODErrorThreshold,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UGaussianSplatComponent Property Definitions *******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UPrimitiveComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UGaussianSplatComponent,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UGaussianSplatComponent_StaticRegisterNativesUGaussianSplatComponent()
{
	UClass* Class = UGaussianSplatComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGaussianSplatComponent;
UClass* Z_Construct_UClass_UGaussianSplatComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UGaussianSplatComponent;
		if (!Z_Registration_Info_UClass_UGaussianSplatComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("GaussianSplatComponent"),
				Z_Registration_Info_UClass_UGaussianSplatComponent.InnerSingleton,
				UGaussianSplatComponent_StaticRegisterNativesUGaussianSplatComponent,
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
		return Z_Registration_Info_UClass_UGaussianSplatComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UGaussianSplatComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplatComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplatComponent.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UGaussianSplatComponent);
UGaussianSplatComponent::~UGaussianSplatComponent() {}
// ********** End Class UGaussianSplatComponent ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h__Script_NanoGS_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_NanoGS_EGaussianSplatRenderMode, TEXT("EGaussianSplatRenderMode"), &ZRIE_EGaussianSplatRenderMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2943934863U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplatComponent, TEXT("UGaussianSplatComponent"), &Z_Registration_Info_UClass_UGaussianSplatComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplatComponent), 414951854U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h__Script_NanoGS_cad35a5957c6928c1a55c1d6b456c1741ed2ac83{
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
