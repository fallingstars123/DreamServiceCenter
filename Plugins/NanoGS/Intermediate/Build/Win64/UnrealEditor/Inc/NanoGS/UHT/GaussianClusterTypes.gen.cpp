// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianClusterTypes.h"
#include "GaussianDataTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianClusterTypes() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector3f(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianCluster(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianClusterHierarchy(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianGPUCluster(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatData(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FGaussianCluster **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FGaussianCluster_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FGaussianCluster>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGaussianCluster); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Single cluster in the hierarchical structure\n * Represents a group of spatially-local splats with bounding volume\n *\n * Hierarchy structure:\n *   Level 0 (leaves): Original splats grouped into clusters\n *   Level 1+: Parent clusters containing merged/simplified splats\n *   Root: Single cluster covering entire point cloud\n */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Single cluster in the hierarchical structure\nRepresents a group of spatially-local splats with bounding volume\n\nHierarchy structure:\n  Level 0 (leaves): Original splats grouped into clusters\n  Level 1+: Parent clusters containing merged/simplified splats\n  Root: Single cluster covering entire point cloud" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClusterID_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unique identifier for this cluster */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unique identifier for this cluster" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParentClusterID_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Parent cluster ID (InvalidClusterID for root) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Parent cluster ID (InvalidClusterID for root)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChildClusterIDs_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Child cluster IDs (empty for leaf clusters) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Child cluster IDs (empty for leaf clusters)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LODLevel_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** LOD level (0 = finest/leaf, increases toward root) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "LOD level (0 = finest/leaf, increases toward root)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsMin_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Axis-aligned bounding box minimum */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Axis-aligned bounding box minimum" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsMax_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Axis-aligned bounding box maximum */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Axis-aligned bounding box maximum" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundingSphereCenter_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Bounding sphere center */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bounding sphere center" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundingSphereRadius_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Bounding sphere radius */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bounding sphere radius" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplatStartIndex_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Start index into the splat array for this cluster's splats */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Start index into the splat array for this cluster's splats" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplatCount_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of splats in this cluster (for leaf) or total descendant splats (for parent) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of splats in this cluster (for leaf) or total descendant splats (for parent)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxError_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Maximum screen-space error if this cluster's LOD is used instead of children\n\x09 * Measured in world units - projected to screen pixels at runtime\n\x09 * For leaf clusters, this is 0 (no simplification error)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum screen-space error if this cluster's LOD is used instead of children\nMeasured in world units - projected to screen pixels at runtime\nFor leaf clusters, this is 0 (no simplification error)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LODSplatStartIndex_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Start index into LODSplats array for this cluster's simplified splats\n\x09 * Only valid for non-leaf clusters (LODLevel > 0)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Start index into LODSplats array for this cluster's simplified splats\nOnly valid for non-leaf clusters (LODLevel > 0)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LODSplatCount_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Number of LOD splats for this cluster\n\x09 * For leaf clusters, this is 0 (use original splats)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of LOD splats for this cluster\nFor leaf clusters, this is 0 (use original splats)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGaussianCluster constinit property declarations ******************
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_ClusterID;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_ParentClusterID;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_ChildClusterIDs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChildClusterIDs;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_LODLevel;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundsMin;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundsMax;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundingSphereCenter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BoundingSphereRadius;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_SplatStartIndex;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_SplatCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxError;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_LODSplatStartIndex;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_LODSplatCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FGaussianCluster constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianCluster>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FGaussianCluster Property Definitions *****************************
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_ClusterID = { "ClusterID", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, ClusterID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClusterID_MetaData), NewProp_ClusterID_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_ParentClusterID = { "ParentClusterID", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, ParentClusterID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParentClusterID_MetaData), NewProp_ParentClusterID_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_ChildClusterIDs_Inner = { "ChildClusterIDs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ChildClusterIDs = { "ChildClusterIDs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, ChildClusterIDs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChildClusterIDs_MetaData), NewProp_ChildClusterIDs_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_LODLevel = { "LODLevel", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, LODLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LODLevel_MetaData), NewProp_LODLevel_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_BoundsMin = { "BoundsMin", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, BoundsMin), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsMin_MetaData), NewProp_BoundsMin_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_BoundsMax = { "BoundsMax", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, BoundsMax), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsMax_MetaData), NewProp_BoundsMax_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_BoundingSphereCenter = { "BoundingSphereCenter", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, BoundingSphereCenter), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundingSphereCenter_MetaData), NewProp_BoundingSphereCenter_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BoundingSphereRadius = { "BoundingSphereRadius", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, BoundingSphereRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundingSphereRadius_MetaData), NewProp_BoundingSphereRadius_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_SplatStartIndex = { "SplatStartIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, SplatStartIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplatStartIndex_MetaData), NewProp_SplatStartIndex_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_SplatCount = { "SplatCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, SplatCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplatCount_MetaData), NewProp_SplatCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxError = { "MaxError", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, MaxError), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxError_MetaData), NewProp_MaxError_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_LODSplatStartIndex = { "LODSplatStartIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, LODSplatStartIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LODSplatStartIndex_MetaData), NewProp_LODSplatStartIndex_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_LODSplatCount = { "LODSplatCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianCluster, LODSplatCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LODSplatCount_MetaData), NewProp_LODSplatCount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClusterID,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ParentClusterID,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChildClusterIDs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChildClusterIDs,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LODLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BoundsMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BoundsMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BoundingSphereCenter,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BoundingSphereRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SplatStartIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SplatCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LODSplatStartIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LODSplatCount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FGaussianCluster Property Definitions *******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	&NewStructOps,
	"GaussianCluster",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FGaussianCluster>(),
	alignof(FGaussianCluster),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGaussianCluster;
UScriptStruct* Z_Construct_UScriptStruct_FGaussianCluster(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FGaussianCluster.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FGaussianCluster.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianCluster, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("GaussianCluster"));
		}
		return Z_Registration_Info_UScriptStruct_FGaussianCluster.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FGaussianCluster.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGaussianCluster.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGaussianCluster.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FGaussianCluster ****************************************************

// ********** Begin ScriptStruct FGaussianGPUCluster ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FGaussianGPUCluster_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FGaussianGPUCluster>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGaussianGPUCluster); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * GPU-friendly cluster data for upload to structured buffer\n * Matches HLSL struct in ClusterData.ush\n * Total: 64 bytes (cache-line aligned)\n */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GPU-friendly cluster data for upload to structured buffer\nMatches HLSL struct in ClusterData.ush\nTotal: 64 bytes (cache-line aligned)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGaussianGPUCluster constinit property declarations ***************
// ********** End ScriptStruct FGaussianGPUCluster constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianGPUCluster>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	&NewStructOps,
	"GaussianGPUCluster",
	nullptr,
	0,
	DataSizeOf<FGaussianGPUCluster>(),
	alignof(FGaussianGPUCluster),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGaussianGPUCluster;
UScriptStruct* Z_Construct_UScriptStruct_FGaussianGPUCluster(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FGaussianGPUCluster.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FGaussianGPUCluster.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianGPUCluster, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("GaussianGPUCluster"));
		}
		return Z_Registration_Info_UScriptStruct_FGaussianGPUCluster.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FGaussianGPUCluster.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGaussianGPUCluster.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGaussianGPUCluster.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FGaussianGPUCluster *************************************************

// ********** Begin ScriptStruct FGaussianClusterHierarchy *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FGaussianClusterHierarchy_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FGaussianClusterHierarchy>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGaussianClusterHierarchy); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Complete cluster hierarchy for a Gaussian Splat asset\n * Built during import, used at runtime for culling and LOD selection\n */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Complete cluster hierarchy for a Gaussian Splat asset\nBuilt during import, used at runtime for culling and LOD selection" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Clusters_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All clusters in the hierarchy (sorted by LOD level, then by cluster ID) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All clusters in the hierarchy (sorted by LOD level, then by cluster ID)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumLODLevels_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of LOD levels (0 = leaf only, 1+ = has parent levels) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of LOD levels (0 = leaf only, 1+ = has parent levels)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplatsPerCluster_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of splats per leaf cluster (used during build) */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of splats per leaf cluster (used during build)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RootClusterIndex_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Index of root cluster in Clusters array */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Index of root cluster in Clusters array" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumLeafClusters_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of leaf clusters */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of leaf clusters" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalSplatCount_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Total number of splats covered by this hierarchy */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Total number of splats covered by this hierarchy" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LODSplats_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * LOD splats for non-leaf clusters (unified format with original splats)\n\x09 * Each non-leaf cluster has simplified splats representing its children\n\x09 * Indexed by FGaussianCluster::LODSplatStartIndex and LODSplatCount\n\x09 * NOTE: These are stored temporarily during build, then appended to main splat array\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "LOD splats for non-leaf clusters (unified format with original splats)\nEach non-leaf cluster has simplified splats representing its children\nIndexed by FGaussianCluster::LODSplatStartIndex and LODSplatCount\nNOTE: These are stored temporarily during build, then appended to main splat array" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalLODSplatCount_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Total number of LOD splats */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianClusterTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Total number of LOD splats" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGaussianClusterHierarchy constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Clusters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Clusters;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_NumLODLevels;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_SplatsPerCluster;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_RootClusterIndex;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_NumLeafClusters;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_TotalSplatCount;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LODSplats_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_LODSplats;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_TotalLODSplatCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FGaussianClusterHierarchy constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianClusterHierarchy>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FGaussianClusterHierarchy Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Clusters_Inner = { "Clusters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGaussianCluster, METADATA_PARAMS(0, nullptr) }; // 8cbab7d633fc9cb04a982c9ec090fa94863def77
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Clusters = { "Clusters", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, Clusters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Clusters_MetaData), NewProp_Clusters_MetaData) }; // 8cbab7d633fc9cb04a982c9ec090fa94863def77
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_NumLODLevels = { "NumLODLevels", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, NumLODLevels), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumLODLevels_MetaData), NewProp_NumLODLevels_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_SplatsPerCluster = { "SplatsPerCluster", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, SplatsPerCluster), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplatsPerCluster_MetaData), NewProp_SplatsPerCluster_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_RootClusterIndex = { "RootClusterIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, RootClusterIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RootClusterIndex_MetaData), NewProp_RootClusterIndex_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_NumLeafClusters = { "NumLeafClusters", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, NumLeafClusters), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumLeafClusters_MetaData), NewProp_NumLeafClusters_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_TotalSplatCount = { "TotalSplatCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, TotalSplatCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalSplatCount_MetaData), NewProp_TotalSplatCount_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_LODSplats_Inner = { "LODSplats", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGaussianSplatData, METADATA_PARAMS(0, nullptr) }; // 3e979c1e4a08336b2606099078ce52b82e5ab0fb
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_LODSplats = { "LODSplats", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, LODSplats), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LODSplats_MetaData), NewProp_LODSplats_MetaData) }; // 3e979c1e4a08336b2606099078ce52b82e5ab0fb
const UECodeGen_Private::FUInt32PropertyParams UHT_STATICS::NewProp_TotalLODSplatCount = { "TotalLODSplatCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianClusterHierarchy, TotalLODSplatCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalLODSplatCount_MetaData), NewProp_TotalLODSplatCount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Clusters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Clusters,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumLODLevels,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SplatsPerCluster,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RootClusterIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumLeafClusters,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TotalSplatCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LODSplats_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LODSplats,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TotalLODSplatCount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FGaussianClusterHierarchy Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	&NewStructOps,
	"GaussianClusterHierarchy",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FGaussianClusterHierarchy>(),
	alignof(FGaussianClusterHierarchy),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy;
UScriptStruct* Z_Construct_UScriptStruct_FGaussianClusterHierarchy(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianClusterHierarchy, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("GaussianClusterHierarchy"));
		}
		return Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FGaussianClusterHierarchy *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianClusterTypes_h__Script_NanoGS_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FGaussianCluster, Z_Construct_UScriptStruct_FGaussianCluster_Statics::NewStructOps, TEXT("GaussianCluster"),&Z_Registration_Info_UScriptStruct_FGaussianCluster, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianCluster), 2361046998U) },
		{ Z_Construct_UScriptStruct_FGaussianGPUCluster, Z_Construct_UScriptStruct_FGaussianGPUCluster_Statics::NewStructOps, TEXT("GaussianGPUCluster"),&Z_Registration_Info_UScriptStruct_FGaussianGPUCluster, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianGPUCluster), 3392902952U) },
		{ Z_Construct_UScriptStruct_FGaussianClusterHierarchy, Z_Construct_UScriptStruct_FGaussianClusterHierarchy_Statics::NewStructOps, TEXT("GaussianClusterHierarchy"),&Z_Registration_Info_UScriptStruct_FGaussianClusterHierarchy, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianClusterHierarchy), 3007864164U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianClusterTypes_h__Script_NanoGS_ee7d4c67836819ce00725bb2e022011ea08514fe{
	TEXT("/Script/NanoGS"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
