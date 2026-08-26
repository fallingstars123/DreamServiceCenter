// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GaussianDataTypes.h"

#ifdef NANOGS_GaussianDataTypes_generated_h
#error "GaussianDataTypes.generated.h already included, missing '#pragma once' in GaussianDataTypes.h"
#endif
#define NANOGS_GaussianDataTypes_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FGaussianSplatData ************************************************
struct Z_Construct_UScriptStruct_FGaussianSplatData_Statics;
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatData(ETypeConstructPhase);

#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianDataTypes_h_69_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FGaussianSplatData_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FGaussianSplatData(ETypeConstructPhase::Inner); }


struct FGaussianSplatData;
// ********** End ScriptStruct FGaussianSplatData **************************************************

// ********** Begin ScriptStruct FGaussianSplatViewData ********************************************
struct Z_Construct_UScriptStruct_FGaussianSplatViewData_Statics;
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplatViewData(ETypeConstructPhase);

#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianDataTypes_h_121_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FGaussianSplatViewData_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FGaussianSplatViewData(ETypeConstructPhase::Inner); }


struct FGaussianSplatViewData;
// ********** End ScriptStruct FGaussianSplatViewData **********************************************

// ********** Begin ScriptStruct FGaussianChunkInfo ************************************************
struct Z_Construct_UScriptStruct_FGaussianChunkInfo_Statics;
NANOGS_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianChunkInfo(ETypeConstructPhase);

#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianDataTypes_h_159_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FGaussianChunkInfo_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FGaussianChunkInfo(ETypeConstructPhase::Inner); }


struct FGaussianChunkInfo;
// ********** End ScriptStruct FGaussianChunkInfo **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianDataTypes_h

// ********** Begin Enum EGaussianPositionFormat ***************************************************
#define FOREACH_ENUM_EGAUSSIANPOSITIONFORMAT(op) \
	op(EGaussianPositionFormat::Float32) \
	op(EGaussianPositionFormat::Norm16) \
	op(EGaussianPositionFormat::Norm11) \
	op(EGaussianPositionFormat::Norm6) 

enum class EGaussianPositionFormat : uint8;
template<> struct TIsUEnumClass<EGaussianPositionFormat> { enum { Value = true }; };
template<> UE_NODEBUG NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianPositionFormat>();
// ********** End Enum EGaussianPositionFormat *****************************************************

// ********** Begin Enum EGaussianColorFormat ******************************************************
#define FOREACH_ENUM_EGAUSSIANCOLORFORMAT(op) \
	op(EGaussianColorFormat::Float32x4) \
	op(EGaussianColorFormat::Float16x4) \
	op(EGaussianColorFormat::Norm8x4) \
	op(EGaussianColorFormat::BC7) 

enum class EGaussianColorFormat : uint8;
template<> struct TIsUEnumClass<EGaussianColorFormat> { enum { Value = true }; };
template<> UE_NODEBUG NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianColorFormat>();
// ********** End Enum EGaussianColorFormat ********************************************************

// ********** Begin Enum EGaussianSHFormat *********************************************************
#define FOREACH_ENUM_EGAUSSIANSHFORMAT(op) \
	op(EGaussianSHFormat::Float32) \
	op(EGaussianSHFormat::Float16) \
	op(EGaussianSHFormat::Norm11) \
	op(EGaussianSHFormat::Norm6) \
	op(EGaussianSHFormat::Cluster4k) \
	op(EGaussianSHFormat::Cluster8k) \
	op(EGaussianSHFormat::Cluster16k) \
	op(EGaussianSHFormat::Cluster32k) \
	op(EGaussianSHFormat::Cluster64k) 

enum class EGaussianSHFormat : uint8;
template<> struct TIsUEnumClass<EGaussianSHFormat> { enum { Value = true }; };
template<> UE_NODEBUG NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianSHFormat>();
// ********** End Enum EGaussianSHFormat ***********************************************************

// ********** Begin Enum EGaussianQualityLevel *****************************************************
#define FOREACH_ENUM_EGAUSSIANQUALITYLEVEL(op) \
	op(EGaussianQualityLevel::VeryHigh) \
	op(EGaussianQualityLevel::High) \
	op(EGaussianQualityLevel::Medium) \
	op(EGaussianQualityLevel::Low) \
	op(EGaussianQualityLevel::VeryLow) 

enum class EGaussianQualityLevel : uint8;
template<> struct TIsUEnumClass<EGaussianQualityLevel> { enum { Value = true }; };
template<> UE_NODEBUG NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianQualityLevel>();
// ********** End Enum EGaussianQualityLevel *******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
