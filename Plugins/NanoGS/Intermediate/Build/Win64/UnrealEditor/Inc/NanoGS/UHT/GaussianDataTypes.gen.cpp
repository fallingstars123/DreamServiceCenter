// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianDataTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeGaussianDataTypes() {}

// ********** Begin Cross Module References ********************************************************
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianColorFormat(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianPositionFormat(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianQualityLevel(ETypeConstructPhase);
NANOGS_API UEnum* Z_Construct_UEnum_NanoGS_EGaussianSHFormat(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianChunkInfo(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatData(ETypeConstructPhase);
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatViewData(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EGaussianPositionFormat ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_NanoGS_EGaussianPositionFormat_Statics
template<> NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianPositionFormat>()
{
	return Z_Construct_UEnum_NanoGS_EGaussianPositionFormat(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Position data compression format\n */" },
#endif
		{ "Float32.DisplayName", "Float32 (12 bytes)" },
		{ "Float32.Name", "EGaussianPositionFormat::Float32" },
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
		{ "Norm11.DisplayName", "Norm11 (4 bytes)" },
		{ "Norm11.Name", "EGaussianPositionFormat::Norm11" },
		{ "Norm16.DisplayName", "Norm16 (6 bytes)" },
		{ "Norm16.Name", "EGaussianPositionFormat::Norm16" },
		{ "Norm6.DisplayName", "Norm6 (2 bytes)" },
		{ "Norm6.Name", "EGaussianPositionFormat::Norm6" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Position data compression format" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianPositionFormat::Float32", (int64)EGaussianPositionFormat::Float32 },
		{ "EGaussianPositionFormat::Norm16", (int64)EGaussianPositionFormat::Norm16 },
		{ "EGaussianPositionFormat::Norm11", (int64)EGaussianPositionFormat::Norm11 },
		{ "EGaussianPositionFormat::Norm6", (int64)EGaussianPositionFormat::Norm6 },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	"EGaussianPositionFormat",
	"EGaussianPositionFormat",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EGaussianPositionFormat;
UEnum* Z_Construct_UEnum_NanoGS_EGaussianPositionFormat(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EGaussianPositionFormat.OuterSingleton)
		{
			ZRIE_EGaussianPositionFormat.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_NanoGS_EGaussianPositionFormat, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("EGaussianPositionFormat"));
		}
		return ZRIE_EGaussianPositionFormat.OuterSingleton;
	}
	if (!ZRIE_EGaussianPositionFormat.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EGaussianPositionFormat.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EGaussianPositionFormat.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EGaussianPositionFormat *****************************************************

// ********** Begin Enum EGaussianColorFormat ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_NanoGS_EGaussianColorFormat_Statics
template<> NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianColorFormat>()
{
	return Z_Construct_UEnum_NanoGS_EGaussianColorFormat(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BC7.DisplayName", "BC7 (~1 byte)" },
		{ "BC7.Name", "EGaussianColorFormat::BC7" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Color/opacity data compression format\n */" },
#endif
		{ "Float16x4.DisplayName", "Float16x4 (8 bytes)" },
		{ "Float16x4.Name", "EGaussianColorFormat::Float16x4" },
		{ "Float32x4.DisplayName", "Float32x4 (16 bytes)" },
		{ "Float32x4.Name", "EGaussianColorFormat::Float32x4" },
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
		{ "Norm8x4.DisplayName", "Norm8x4 (4 bytes)" },
		{ "Norm8x4.Name", "EGaussianColorFormat::Norm8x4" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color/opacity data compression format" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianColorFormat::Float32x4", (int64)EGaussianColorFormat::Float32x4 },
		{ "EGaussianColorFormat::Float16x4", (int64)EGaussianColorFormat::Float16x4 },
		{ "EGaussianColorFormat::Norm8x4", (int64)EGaussianColorFormat::Norm8x4 },
		{ "EGaussianColorFormat::BC7", (int64)EGaussianColorFormat::BC7 },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	"EGaussianColorFormat",
	"EGaussianColorFormat",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EGaussianColorFormat;
UEnum* Z_Construct_UEnum_NanoGS_EGaussianColorFormat(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EGaussianColorFormat.OuterSingleton)
		{
			ZRIE_EGaussianColorFormat.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_NanoGS_EGaussianColorFormat, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("EGaussianColorFormat"));
		}
		return ZRIE_EGaussianColorFormat.OuterSingleton;
	}
	if (!ZRIE_EGaussianColorFormat.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EGaussianColorFormat.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EGaussianColorFormat.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EGaussianColorFormat ********************************************************

// ********** Begin Enum EGaussianSHFormat *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_NanoGS_EGaussianSHFormat_Statics
template<> NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianSHFormat>()
{
	return Z_Construct_UEnum_NanoGS_EGaussianSHFormat(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Cluster16k.DisplayName", "Cluster 16k" },
		{ "Cluster16k.Name", "EGaussianSHFormat::Cluster16k" },
		{ "Cluster32k.DisplayName", "Cluster 32k" },
		{ "Cluster32k.Name", "EGaussianSHFormat::Cluster32k" },
		{ "Cluster4k.DisplayName", "Cluster 4k" },
		{ "Cluster4k.Name", "EGaussianSHFormat::Cluster4k" },
		{ "Cluster64k.DisplayName", "Cluster 64k" },
		{ "Cluster64k.Name", "EGaussianSHFormat::Cluster64k" },
		{ "Cluster8k.DisplayName", "Cluster 8k" },
		{ "Cluster8k.Name", "EGaussianSHFormat::Cluster8k" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Spherical harmonics compression format\n */" },
#endif
		{ "Float16.DisplayName", "Float16" },
		{ "Float16.Name", "EGaussianSHFormat::Float16" },
		{ "Float32.DisplayName", "Float32" },
		{ "Float32.Name", "EGaussianSHFormat::Float32" },
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
		{ "Norm11.DisplayName", "Norm11" },
		{ "Norm11.Name", "EGaussianSHFormat::Norm11" },
		{ "Norm6.DisplayName", "Norm6" },
		{ "Norm6.Name", "EGaussianSHFormat::Norm6" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spherical harmonics compression format" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSHFormat::Float32", (int64)EGaussianSHFormat::Float32 },
		{ "EGaussianSHFormat::Float16", (int64)EGaussianSHFormat::Float16 },
		{ "EGaussianSHFormat::Norm11", (int64)EGaussianSHFormat::Norm11 },
		{ "EGaussianSHFormat::Norm6", (int64)EGaussianSHFormat::Norm6 },
		{ "EGaussianSHFormat::Cluster4k", (int64)EGaussianSHFormat::Cluster4k },
		{ "EGaussianSHFormat::Cluster8k", (int64)EGaussianSHFormat::Cluster8k },
		{ "EGaussianSHFormat::Cluster16k", (int64)EGaussianSHFormat::Cluster16k },
		{ "EGaussianSHFormat::Cluster32k", (int64)EGaussianSHFormat::Cluster32k },
		{ "EGaussianSHFormat::Cluster64k", (int64)EGaussianSHFormat::Cluster64k },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	"EGaussianSHFormat",
	"EGaussianSHFormat",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EGaussianSHFormat;
UEnum* Z_Construct_UEnum_NanoGS_EGaussianSHFormat(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EGaussianSHFormat.OuterSingleton)
		{
			ZRIE_EGaussianSHFormat.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_NanoGS_EGaussianSHFormat, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("EGaussianSHFormat"));
		}
		return ZRIE_EGaussianSHFormat.OuterSingleton;
	}
	if (!ZRIE_EGaussianSHFormat.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EGaussianSHFormat.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EGaussianSHFormat.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EGaussianSHFormat ***********************************************************

// ********** Begin Enum EGaussianQualityLevel *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_NanoGS_EGaussianQualityLevel_Statics
template<> NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianQualityLevel>()
{
	return Z_Construct_UEnum_NanoGS_EGaussianQualityLevel(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Quality level preset for import\n */" },
#endif
		{ "High.DisplayName", "High (~24 bytes/splat)" },
		{ "High.Name", "EGaussianQualityLevel::High" },
		{ "Low.DisplayName", "Low (~8 bytes/splat)" },
		{ "Low.Name", "EGaussianQualityLevel::Low" },
		{ "Medium.DisplayName", "Medium (~12 bytes/splat)" },
		{ "Medium.Name", "EGaussianQualityLevel::Medium" },
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Quality level preset for import" },
#endif
		{ "VeryHigh.DisplayName", "Very High (~48 bytes/splat)" },
		{ "VeryHigh.Name", "EGaussianQualityLevel::VeryHigh" },
		{ "VeryLow.DisplayName", "Very Low (~4 bytes/splat)" },
		{ "VeryLow.Name", "EGaussianQualityLevel::VeryLow" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianQualityLevel::VeryHigh", (int64)EGaussianQualityLevel::VeryHigh },
		{ "EGaussianQualityLevel::High", (int64)EGaussianQualityLevel::High },
		{ "EGaussianQualityLevel::Medium", (int64)EGaussianQualityLevel::Medium },
		{ "EGaussianQualityLevel::Low", (int64)EGaussianQualityLevel::Low },
		{ "EGaussianQualityLevel::VeryLow", (int64)EGaussianQualityLevel::VeryLow },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	"EGaussianQualityLevel",
	"EGaussianQualityLevel",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EGaussianQualityLevel;
UEnum* Z_Construct_UEnum_NanoGS_EGaussianQualityLevel(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EGaussianQualityLevel.OuterSingleton)
		{
			ZRIE_EGaussianQualityLevel.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_NanoGS_EGaussianQualityLevel, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("EGaussianQualityLevel"));
		}
		return ZRIE_EGaussianQualityLevel.OuterSingleton;
	}
	if (!ZRIE_EGaussianQualityLevel.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EGaussianQualityLevel.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EGaussianQualityLevel.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EGaussianQualityLevel *******************************************************

// ********** Begin ScriptStruct FGaussianSplatData ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FGaussianSplatData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FGaussianSplatData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGaussianSplatData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Raw splat data read from PLY file (CPU-side, before compression)\n * Total: ~248 bytes per splat\n */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Raw splat data read from PLY file (CPU-side, before compression)\nTotal: ~248 bytes per splat" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGaussianSplatData constinit property declarations ****************
// ********** End ScriptStruct FGaussianSplatData constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianSplatData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	&NewStructOps,
	"GaussianSplatData",
	nullptr,
	0,
	DataSizeOf<FGaussianSplatData>(),
	alignof(FGaussianSplatData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGaussianSplatData;
UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FGaussianSplatData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FGaussianSplatData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianSplatData, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("GaussianSplatData"));
		}
		return Z_Registration_Info_UScriptStruct_FGaussianSplatData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FGaussianSplatData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGaussianSplatData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGaussianSplatData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FGaussianSplatData **************************************************

// ********** Begin ScriptStruct FGaussianSplatViewData ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FGaussianSplatViewData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FGaussianSplatViewData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGaussianSplatViewData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Per-frame view data computed by compute shader, used by vertex shader\n * This structure must match the HLSL definition in GaussianDataTypes.ush\n * Total: 64 bytes per splat (with TranslatedWorldPos for velocity, 16-byte aligned)\n */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Per-frame view data computed by compute shader, used by vertex shader\nThis structure must match the HLSL definition in GaussianDataTypes.ush\nTotal: 64 bytes per splat (with TranslatedWorldPos for velocity, 16-byte aligned)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGaussianSplatViewData constinit property declarations ************
// ********** End ScriptStruct FGaussianSplatViewData constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianSplatViewData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	&NewStructOps,
	"GaussianSplatViewData",
	nullptr,
	0,
	DataSizeOf<FGaussianSplatViewData>(),
	alignof(FGaussianSplatViewData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGaussianSplatViewData;
UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatViewData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FGaussianSplatViewData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FGaussianSplatViewData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianSplatViewData, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("GaussianSplatViewData"));
		}
		return Z_Registration_Info_UScriptStruct_FGaussianSplatViewData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FGaussianSplatViewData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGaussianSplatViewData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGaussianSplatViewData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FGaussianSplatViewData **********************************************

// ********** Begin ScriptStruct FGaussianChunkInfo ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FGaussianChunkInfo_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FGaussianChunkInfo>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGaussianChunkInfo); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Chunk info for quantized/compressed data\n * Each chunk contains 256 splats with shared min/max bounds for dequantization\n * Total: 72 bytes per chunk\n */" },
#endif
		{ "ModuleRelativePath", "Public/GaussianDataTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Chunk info for quantized/compressed data\nEach chunk contains 256 splats with shared min/max bounds for dequantization\nTotal: 72 bytes per chunk" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGaussianChunkInfo constinit property declarations ****************
// ********** End ScriptStruct FGaussianChunkInfo constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianChunkInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_NanoGS,
	nullptr,
	&NewStructOps,
	"GaussianChunkInfo",
	nullptr,
	0,
	DataSizeOf<FGaussianChunkInfo>(),
	alignof(FGaussianChunkInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGaussianChunkInfo;
UScriptStruct* Z_Construct_UScriptStruct_FGaussianChunkInfo(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FGaussianChunkInfo.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FGaussianChunkInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianChunkInfo, (UObject*)Z_Construct_UPackage__Script_NanoGS(ETypeConstructPhase::Outer), TEXT("GaussianChunkInfo"));
		}
		return Z_Registration_Info_UScriptStruct_FGaussianChunkInfo.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FGaussianChunkInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGaussianChunkInfo.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGaussianChunkInfo.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FGaussianChunkInfo **************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianDataTypes_h__Script_NanoGS_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_NanoGS_EGaussianPositionFormat, TEXT("EGaussianPositionFormat"), &ZRIE_EGaussianPositionFormat, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3400859710U) },
		{ Z_Construct_UEnum_NanoGS_EGaussianColorFormat, TEXT("EGaussianColorFormat"), &ZRIE_EGaussianColorFormat, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 142386165U) },
		{ Z_Construct_UEnum_NanoGS_EGaussianSHFormat, TEXT("EGaussianSHFormat"), &ZRIE_EGaussianSHFormat, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2426764064U) },
		{ Z_Construct_UEnum_NanoGS_EGaussianQualityLevel, TEXT("EGaussianQualityLevel"), &ZRIE_EGaussianQualityLevel, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2470270492U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FGaussianSplatData, Z_Construct_UScriptStruct_FGaussianSplatData_Statics::NewStructOps, TEXT("GaussianSplatData"),&Z_Registration_Info_UScriptStruct_FGaussianSplatData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianSplatData), 1050123294U) },
		{ Z_Construct_UScriptStruct_FGaussianSplatViewData, Z_Construct_UScriptStruct_FGaussianSplatViewData_Statics::NewStructOps, TEXT("GaussianSplatViewData"),&Z_Registration_Info_UScriptStruct_FGaussianSplatViewData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianSplatViewData), 726680424U) },
		{ Z_Construct_UScriptStruct_FGaussianChunkInfo, Z_Construct_UScriptStruct_FGaussianChunkInfo_Statics::NewStructOps, TEXT("GaussianChunkInfo"),&Z_Registration_Info_UScriptStruct_FGaussianChunkInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianChunkInfo), 1315642207U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianDataTypes_h__Script_NanoGS_754e4fefc9982bc6ddca49dd3710dbca72f0dfbb{
	TEXT("/Script/NanoGS"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
