// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplatAsset.h"
#include "GaussianClusterTypes.h"
#include "GaussianDataTypes.h"
#include "Serialization/ArchiveUObjectFromStructuredArchive.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianSplatAsset() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FBox(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UObject(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UTexture2D(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianColorFormat(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianPositionFormat(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianQualityLevel(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianSHFormat(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianChunkInfo(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianClusterHierarchy(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatAsset(ETypeConstructPhase);
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatAsset(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UGaussianSplatAsset Function BuildNaniteClusterHierarchy *****************
#if WITH_EDITOR
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_BuildNaniteClusterHierarchy_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventBuildNaniteClusterHierarchy_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Nanite" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Build Nanite cluster hierarchy from source PLY file\n\x09 * This re-reads the source file and builds cluster data\n\x09 * @return True if successful, false if source file not found or build failed\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Build Nanite cluster hierarchy from source PLY file\nThis re-reads the source file and builds cluster data\n@return True if successful, false if source file not found or build failed" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BuildNaniteClusterHierarchy constinit property declarations ***********
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GaussianSplatAsset_eventBuildNaniteClusterHierarchy_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BuildNaniteClusterHierarchy constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BuildNaniteClusterHierarchy Property Definitions **********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(GaussianSplatAsset_eventBuildNaniteClusterHierarchy_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BuildNaniteClusterHierarchy Property Definitions ************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "BuildNaniteClusterHierarchy", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventBuildNaniteClusterHierarchy_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x24020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventBuildNaniteClusterHierarchy_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_BuildNaniteClusterHierarchy(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execBuildNaniteClusterHierarchy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->BuildNaniteClusterHierarchy();
	P_NATIVE_END;
}
#endif
// ********** End Class UGaussianSplatAsset Function BuildNaniteClusterHierarchy *******************

// ********** Begin Class UGaussianSplatAsset Function ClearNaniteClusterHierarchy *****************
#if WITH_EDITOR
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_ClearNaniteClusterHierarchy_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Nanite" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Clear Nanite cluster hierarchy to reduce asset size\n\x09 * Removes cluster data and LOD splats\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Clear Nanite cluster hierarchy to reduce asset size\nRemoves cluster data and LOD splats" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClearNaniteClusterHierarchy constinit property declarations ***********
// ********** End Function ClearNaniteClusterHierarchy constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "ClearNaniteClusterHierarchy", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x24020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_ClearNaniteClusterHierarchy(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execClearNaniteClusterHierarchy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearNaniteClusterHierarchy();
	P_NATIVE_END;
}
#endif
// ********** End Class UGaussianSplatAsset Function ClearNaniteClusterHierarchy *******************

// ********** Begin Class UGaussianSplatAsset Function GetBounds ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetBounds_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetBounds_Parms
	{
		FBox ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the bounding box of all splats */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the bounding box of all splats" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetBounds constinit property declarations *****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetBounds constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetBounds Property Definitions ****************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetBounds_Parms, ReturnValue), Z_Construct_UScriptStruct_FBox, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetBounds Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetBounds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetBounds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetBounds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetBounds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetBounds)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBox*)Z_Param__Result=P_THIS->GetBounds();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetBounds *************************************

// ********** Begin Class UGaussianSplatAsset Function GetClusterCount *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetClusterCount_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetClusterCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Clustering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get number of clusters in hierarchy */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get number of clusters in hierarchy" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetClusterCount constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetClusterCount constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetClusterCount Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetClusterCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetClusterCount Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetClusterCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetClusterCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetClusterCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetClusterCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetClusterCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetClusterCount();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetClusterCount *******************************

// ********** Begin Class UGaussianSplatAsset Function GetDecompressedPositions ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetDecompressedPositions_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetDecompressedPositions_Parms
	{
		TArray<FVector> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Decompress and return all splat positions (for debugging)\n\x09 * @return Array of world-space positions\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Decompress and return all splat positions (for debugging)\n@return Array of world-space positions" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDecompressedPositions constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDecompressedPositions constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDecompressedPositions Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetDecompressedPositions_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDecompressedPositions Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetDecompressedPositions", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetDecompressedPositions_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetDecompressedPositions_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetDecompressedPositions(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetDecompressedPositions)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FVector>*)Z_Param__Result=P_THIS->GetDecompressedPositions();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetDecompressedPositions **********************

// ********** Begin Class UGaussianSplatAsset Function GetMemoryUsage ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetMemoryUsage_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetMemoryUsage_Parms
	{
		int64 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get estimated memory usage in bytes */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get estimated memory usage in bytes" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetMemoryUsage constinit property declarations ************************
	static const UECodeGen_Private::FInt64PropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMemoryUsage constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMemoryUsage Property Definitions ***********************************
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetMemoryUsage_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMemoryUsage Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetMemoryUsage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetMemoryUsage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetMemoryUsage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetMemoryUsage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetMemoryUsage)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int64*)Z_Param__Result=P_THIS->GetMemoryUsage();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetMemoryUsage ********************************

// ********** Begin Class UGaussianSplatAsset Function GetNumLODLevels *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetNumLODLevels_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetNumLODLevels_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Clustering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get number of LOD levels */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get number of LOD levels" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetNumLODLevels constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNumLODLevels constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNumLODLevels Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetNumLODLevels_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetNumLODLevels Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetNumLODLevels", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetNumLODLevels_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetNumLODLevels_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetNumLODLevels(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetNumLODLevels)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetNumLODLevels();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetNumLODLevels *******************************

// ********** Begin Class UGaussianSplatAsset Function GetOriginalSplatCount ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetOriginalSplatCount_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetOriginalSplatCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Nanite" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get original splat count (excluding LOD splats) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get original splat count (excluding LOD splats)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetOriginalSplatCount constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetOriginalSplatCount constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetOriginalSplatCount Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetOriginalSplatCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetOriginalSplatCount Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetOriginalSplatCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetOriginalSplatCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetOriginalSplatCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetOriginalSplatCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetOriginalSplatCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetOriginalSplatCount();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetOriginalSplatCount *************************

// ********** Begin Class UGaussianSplatAsset Function GetSplatCount *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_GetSplatCount_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventGetSplatCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the number of splats in this asset */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the number of splats in this asset" },
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
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(GaussianSplatAsset_eventGetSplatCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSplatCount Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "GetSplatCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventGetSplatCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventGetSplatCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_GetSplatCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execGetSplatCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetSplatCount();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function GetSplatCount *********************************

// ********** Begin Class UGaussianSplatAsset Function HasClusterHierarchy *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_HasClusterHierarchy_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventHasClusterHierarchy_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Clustering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Check if cluster hierarchy is available */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if cluster hierarchy is available" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HasClusterHierarchy constinit property declarations *******************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GaussianSplatAsset_eventHasClusterHierarchy_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasClusterHierarchy constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasClusterHierarchy Property Definitions ******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(GaussianSplatAsset_eventHasClusterHierarchy_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasClusterHierarchy Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "HasClusterHierarchy", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventHasClusterHierarchy_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventHasClusterHierarchy_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_HasClusterHierarchy(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execHasClusterHierarchy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasClusterHierarchy();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function HasClusterHierarchy ***************************

// ********** Begin Class UGaussianSplatAsset Function IsNaniteEnabled *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_IsNaniteEnabled_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventIsNaniteEnabled_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting|Nanite" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Check if Nanite is enabled for this asset */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if Nanite is enabled for this asset" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsNaniteEnabled constinit property declarations ***********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GaussianSplatAsset_eventIsNaniteEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsNaniteEnabled constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsNaniteEnabled Property Definitions **********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(GaussianSplatAsset_eventIsNaniteEnabled_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsNaniteEnabled Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "IsNaniteEnabled", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventIsNaniteEnabled_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventIsNaniteEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_IsNaniteEnabled(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execIsNaniteEnabled)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsNaniteEnabled();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function IsNaniteEnabled *******************************

// ********** Begin Class UGaussianSplatAsset Function IsPointCloudAsset ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_IsPointCloudAsset_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventIsPointCloudAsset_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True when this asset was imported from a COLMAP sparse points3D.bin file. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True when this asset was imported from a COLMAP sparse points3D.bin file." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsPointCloudAsset constinit property declarations *********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GaussianSplatAsset_eventIsPointCloudAsset_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsPointCloudAsset constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsPointCloudAsset Property Definitions ********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(GaussianSplatAsset_eventIsPointCloudAsset_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsPointCloudAsset Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "IsPointCloudAsset", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventIsPointCloudAsset_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventIsPointCloudAsset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_IsPointCloudAsset(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execIsPointCloudAsset)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsPointCloudAsset();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function IsPointCloudAsset *****************************

// ********** Begin Class UGaussianSplatAsset Function IsValid *************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UGaussianSplatAsset_IsValid_Statics
struct UHT_STATICS
{
	struct GaussianSplatAsset_eventIsValid_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Gaussian Splatting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Check if asset has valid data */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if asset has valid data" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsValid constinit property declarations *******************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GaussianSplatAsset_eventIsValid_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsValid constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsValid Property Definitions ******************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(GaussianSplatAsset_eventIsValid_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsValid Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UGaussianSplatAsset, nullptr, "IsValid", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::GaussianSplatAsset_eventIsValid_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::GaussianSplatAsset_eventIsValid_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGaussianSplatAsset_IsValid(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UGaussianSplatAsset::execIsValid)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsValid();
	P_NATIVE_END;
}
// ********** End Class UGaussianSplatAsset Function IsValid ***************************************

// ********** Begin Class UGaussianSplatAsset ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UGaussianSplatAsset_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Asset containing Gaussian Splatting data loaded from PLY files\n * Stores compressed splat data optimized for GPU rendering\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "GaussianSplatAsset.h" },
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Asset containing Gaussian Splatting data loaded from PLY files\nStores compressed splat data optimized for GPU rendering" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplatCount_MetaData[] = {
		{ "Category", "Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Total number of splats */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Total number of splats" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundingBox_MetaData[] = {
		{ "Category", "Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** World-space bounding box of all splats */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "World-space bounding box of all splats" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionFormat_MetaData[] = {
		{ "Category", "Format" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Position compression format */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Position compression format" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorFormat_MetaData[] = {
		{ "Category", "Format" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Color compression format */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color compression format" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SHFormat_MetaData[] = {
		{ "Category", "Format" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spherical harmonics compression format */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spherical harmonics compression format" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SHBands_MetaData[] = {
		{ "Category", "Format" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of SH bands stored (0-3) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of SH bands stored (0-3)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Chunk quantization info (one per 256 splats) - kept as TArray since it's small */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Chunk quantization info (one per 256 splats) - kept as TArray since it's small" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorTexture_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Color texture (Morton-swizzled, 2048 x N) - created at runtime from ColorTextureBulkData */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color texture (Morton-swizzled, 2048 x N) - created at runtime from ColorTextureBulkData" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorTextureWidth_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Color texture width */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color texture width" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorTextureHeight_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Color texture height */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color texture height" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceFilePath_MetaData[] = {
		{ "Category", "Import" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Source file path (for reimport) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Source file path (for reimport)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImportQuality_MetaData[] = {
		{ "Category", "Import" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Quality level used during import */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Quality level used during import" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsPointCloudAsset_MetaData[] = {
		{ "Category", "Import" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether this asset represents a sparse point cloud rather than trained Gaussians. */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether this asset represents a sparse point cloud rather than trained Gaussians." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableNanite_MetaData[] = {
		{ "Category", "Nanite" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Whether Nanite-style LOD and culling is enabled for this asset\n\x09 * Enable via Asset Actions > Nanite in Content Browser\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether Nanite-style LOD and culling is enabled for this asset\nEnable via Asset Actions > Nanite in Content Browser" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClusterHierarchy_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Hierarchical cluster structure for Nanite-style LOD and culling\n\x09 * Only populated when bEnableNanite is true\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Hierarchical cluster structure for Nanite-style LOD and culling\nOnly populated when bEnableNanite is true" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OriginalSplatCount_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Number of original splats (before LOD splats are appended)\n\x09 * When Nanite is enabled, SplatCount includes both original + LOD splats\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of original splats (before LOD splats are appended)\nWhen Nanite is enabled, SplatCount includes both original + LOD splats" },
#endif
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThumbnailTexture_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Thumbnail image generated at import time.\n\x09 * Stored persistently in the asset package so the Content Browser can display it.\n\x09 * NOTE: This is Transient - recreated from ThumbnailData in PostLoad()\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Thumbnail image generated at import time.\nStored persistently in the asset package so the Content Browser can display it.\nNOTE: This is Transient - recreated from ThumbnailData in PostLoad()" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThumbnailData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Raw thumbnail pixel data (BGRA, 256x256).\n\x09 * Stored persistently and used to recreate ThumbnailTexture on load.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Raw thumbnail pixel data (BGRA, 256x256).\nStored persistently and used to recreate ThumbnailTexture on load." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThumbnailSize_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Size of the thumbnail (width = height) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianSplatAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Size of the thumbnail (width = height)" },
#endif
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA

// ********** Begin Class UGaussianSplatAsset constinit property declarations **********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SplatCount;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundingBox;
	static const UECodeGen_Private::FBytePropertyParams NewProp_PositionFormat_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PositionFormat;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ColorFormat_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ColorFormat;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SHFormat_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SHFormat;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SHBands;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChunkData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChunkData;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ColorTexture;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ColorTextureWidth;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ColorTextureHeight;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SourceFilePath;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ImportQuality_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ImportQuality;
	static void NewProp_bIsPointCloudAsset_SetBit(void* Obj)
	{
		((UGaussianSplatAsset*)Obj)->bIsPointCloudAsset = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsPointCloudAsset;
	static void NewProp_bEnableNanite_SetBit(void* Obj)
	{
		((UGaussianSplatAsset*)Obj)->bEnableNanite = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableNanite;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ClusterHierarchy;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OriginalSplatCount;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ThumbnailTexture;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ThumbnailData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ThumbnailData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ThumbnailSize;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UGaussianSplatAsset constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
#if WITH_EDITOR
		{ .NameUTF8 = UTF8TEXT("BuildNaniteClusterHierarchy"), .Pointer = &UGaussianSplatAsset::execBuildNaniteClusterHierarchy },
		{ .NameUTF8 = UTF8TEXT("ClearNaniteClusterHierarchy"), .Pointer = &UGaussianSplatAsset::execClearNaniteClusterHierarchy },
#endif // WITH_EDITOR
		{ .NameUTF8 = UTF8TEXT("GetBounds"), .Pointer = &UGaussianSplatAsset::execGetBounds },
		{ .NameUTF8 = UTF8TEXT("GetClusterCount"), .Pointer = &UGaussianSplatAsset::execGetClusterCount },
		{ .NameUTF8 = UTF8TEXT("GetDecompressedPositions"), .Pointer = &UGaussianSplatAsset::execGetDecompressedPositions },
		{ .NameUTF8 = UTF8TEXT("GetMemoryUsage"), .Pointer = &UGaussianSplatAsset::execGetMemoryUsage },
		{ .NameUTF8 = UTF8TEXT("GetNumLODLevels"), .Pointer = &UGaussianSplatAsset::execGetNumLODLevels },
		{ .NameUTF8 = UTF8TEXT("GetOriginalSplatCount"), .Pointer = &UGaussianSplatAsset::execGetOriginalSplatCount },
		{ .NameUTF8 = UTF8TEXT("GetSplatCount"), .Pointer = &UGaussianSplatAsset::execGetSplatCount },
		{ .NameUTF8 = UTF8TEXT("HasClusterHierarchy"), .Pointer = &UGaussianSplatAsset::execHasClusterHierarchy },
		{ .NameUTF8 = UTF8TEXT("IsNaniteEnabled"), .Pointer = &UGaussianSplatAsset::execIsNaniteEnabled },
		{ .NameUTF8 = UTF8TEXT("IsPointCloudAsset"), .Pointer = &UGaussianSplatAsset::execIsPointCloudAsset },
		{ .NameUTF8 = UTF8TEXT("IsValid"), .Pointer = &UGaussianSplatAsset::execIsValid },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
#if WITH_EDITOR
		{ &Z_Construct_UFunction_UGaussianSplatAsset_BuildNaniteClusterHierarchy, "BuildNaniteClusterHierarchy" }, // d95f96eb33155aad39715d6bf5d2200e1e499d4b
		{ &Z_Construct_UFunction_UGaussianSplatAsset_ClearNaniteClusterHierarchy, "ClearNaniteClusterHierarchy" }, // 8f94a92d6bf7fb93a2381b80c401177ffdc55971
#endif // WITH_EDITOR
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetBounds, "GetBounds" }, // 425e2858548db17181f0bf8e1b7e0f5e7c7b574e
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetClusterCount, "GetClusterCount" }, // b8884f68a9638297f42bb51042c46eaf5a502b6f
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetDecompressedPositions, "GetDecompressedPositions" }, // bfc5c091841b2b36bcf1814b069d517c9534a13b
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetMemoryUsage, "GetMemoryUsage" }, // 624f8fa93d9de44c8dde978d4a62e569a7ae8f53
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetNumLODLevels, "GetNumLODLevels" }, // e3328a9e205feef0ae0af59ebd9615940563761e
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetOriginalSplatCount, "GetOriginalSplatCount" }, // 92987a36e2fd078d8d4342c51a46b7e3ef21f75a
		{ &Z_Construct_UFunction_UGaussianSplatAsset_GetSplatCount, "GetSplatCount" }, // 81224392570f66a33362562b8d4ab7bd25944d49
		{ &Z_Construct_UFunction_UGaussianSplatAsset_HasClusterHierarchy, "HasClusterHierarchy" }, // b550e4560b3b9f628bcd5245dbf556789eea2147
		{ &Z_Construct_UFunction_UGaussianSplatAsset_IsNaniteEnabled, "IsNaniteEnabled" }, // 7cf9015efaa8bc4acb21dc5143e00913f05d1958
		{ &Z_Construct_UFunction_UGaussianSplatAsset_IsPointCloudAsset, "IsPointCloudAsset" }, // 7036875a3a3bdbfbb45d17861c44706037418ab3
		{ &Z_Construct_UFunction_UGaussianSplatAsset_IsValid, "IsValid" }, // 2e044b4a4bd67615f8e244a7fc40ed8ea6a208f0
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplatAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UGaussianSplatAsset Property Definitions *********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SplatCount = { "SplatCount", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, SplatCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplatCount_MetaData), NewProp_SplatCount_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_BoundingBox = { "BoundingBox", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, BoundingBox), Z_Construct_UScriptStruct_FBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundingBox_MetaData), NewProp_BoundingBox_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_PositionFormat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_PositionFormat = { "PositionFormat", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, PositionFormat), Z_Construct_UEnum_NanoGS_EGaussianPositionFormat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionFormat_MetaData), NewProp_PositionFormat_MetaData) }; // cab5003e3be8c5984c278881926598a94729d234
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ColorFormat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ColorFormat = { "ColorFormat", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ColorFormat), Z_Construct_UEnum_NanoGS_EGaussianColorFormat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorFormat_MetaData), NewProp_ColorFormat_MetaData) }; // 087ca3f5b2e0fa87b9a8618c1920e17397a53a56
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SHFormat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_SHFormat = { "SHFormat", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, SHFormat), Z_Construct_UEnum_NanoGS_EGaussianSHFormat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SHFormat_MetaData), NewProp_SHFormat_MetaData) }; // 90a57b205c28c3e4609df12ed702fe506eaefcaf
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SHBands = { "SHBands", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, SHBands), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SHBands_MetaData), NewProp_SHBands_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ChunkData_Inner = { "ChunkData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGaussianChunkInfo, METADATA_PARAMS(0, nullptr) }; // 4e6b1b5faad57e5996f2dd25cf16af746b56f7af
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ChunkData = { "ChunkData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ChunkData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkData_MetaData), NewProp_ChunkData_MetaData) }; // 4e6b1b5faad57e5996f2dd25cf16af746b56f7af
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ColorTexture = { "ColorTexture", nullptr, (EPropertyFlags)0x0114000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ColorTexture), Z_Construct_UClass_UTexture2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorTexture_MetaData), NewProp_ColorTexture_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ColorTextureWidth = { "ColorTextureWidth", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ColorTextureWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorTextureWidth_MetaData), NewProp_ColorTextureWidth_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ColorTextureHeight = { "ColorTextureHeight", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ColorTextureHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorTextureHeight_MetaData), NewProp_ColorTextureHeight_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SourceFilePath = { "SourceFilePath", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, SourceFilePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceFilePath_MetaData), NewProp_SourceFilePath_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ImportQuality_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ImportQuality = { "ImportQuality", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ImportQuality), Z_Construct_UEnum_NanoGS_EGaussianQualityLevel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImportQuality_MetaData), NewProp_ImportQuality_MetaData) }; // 933d561c54f36618babf66f5f6006369070be7d9
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIsPointCloudAsset = { "bIsPointCloudAsset", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UGaussianSplatAsset), &UHT_STATICS::NewProp_bIsPointCloudAsset_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsPointCloudAsset_MetaData), NewProp_bIsPointCloudAsset_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEnableNanite = { "bEnableNanite", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UGaussianSplatAsset), &UHT_STATICS::NewProp_bEnableNanite_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableNanite_MetaData), NewProp_bEnableNanite_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ClusterHierarchy = { "ClusterHierarchy", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ClusterHierarchy), Z_Construct_UScriptStruct_FGaussianClusterHierarchy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClusterHierarchy_MetaData), NewProp_ClusterHierarchy_MetaData) }; // b3485d64c87a2055d7022b0f7ed2d5c9dca03413
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_OriginalSplatCount = { "OriginalSplatCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, OriginalSplatCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OriginalSplatCount_MetaData), NewProp_OriginalSplatCount_MetaData) };
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ThumbnailTexture = { "ThumbnailTexture", nullptr, (EPropertyFlags)0x0114000800002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ThumbnailTexture), Z_Construct_UClass_UTexture2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThumbnailTexture_MetaData), NewProp_ThumbnailTexture_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ThumbnailData_Inner = { "ThumbnailData", nullptr, (EPropertyFlags)0x0000000800000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ThumbnailData = { "ThumbnailData", nullptr, (EPropertyFlags)0x0010000800000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ThumbnailData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThumbnailData_MetaData), NewProp_ThumbnailData_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ThumbnailSize = { "ThumbnailSize", nullptr, (EPropertyFlags)0x0010000800000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplatAsset, ThumbnailSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThumbnailSize_MetaData), NewProp_ThumbnailSize_MetaData) };
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SplatCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BoundingBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PositionFormat_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PositionFormat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorFormat_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorFormat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SHFormat_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SHFormat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SHBands,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChunkData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChunkData,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorTextureWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorTextureHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SourceFilePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImportQuality_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImportQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIsPointCloudAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEnableNanite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClusterHierarchy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OriginalSplatCount,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ThumbnailTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ThumbnailData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ThumbnailData,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ThumbnailSize,
#endif // WITH_EDITORONLY_DATA
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UGaussianSplatAsset Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UObject,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UGaussianSplatAsset,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UGaussianSplatAsset_StaticRegisterNativesUGaussianSplatAsset()
{
	UClass* Class = UGaussianSplatAsset::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGaussianSplatAsset;
UClass* Z_Construct_UClass_UGaussianSplatAsset(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UGaussianSplatAsset;
		if (!Z_Registration_Info_UClass_UGaussianSplatAsset.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("GaussianSplatAsset"),
				Z_Registration_Info_UClass_UGaussianSplatAsset.InnerSingleton,
				UGaussianSplatAsset_StaticRegisterNativesUGaussianSplatAsset,
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
		return Z_Registration_Info_UClass_UGaussianSplatAsset.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UGaussianSplatAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplatAsset.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplatAsset.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UGaussianSplatAsset);
UGaussianSplatAsset::~UGaussianSplatAsset() {}
IMPLEMENT_FSTRUCTUREDARCHIVE_SERIALIZER(UGaussianSplatAsset)
// ********** End Class UGaussianSplatAsset ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatAsset_h__Script_NanoGS_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplatAsset, TEXT("UGaussianSplatAsset"), &Z_Registration_Info_UClass_UGaussianSplatAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplatAsset), 1564592070U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatAsset_h__Script_NanoGS_42ac1e529ce2ac4361fd0f94b316756761a8ef04{
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
