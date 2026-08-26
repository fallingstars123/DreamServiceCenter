// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GaussianSplatComponent.h"

#ifdef NANOGS_GaussianSplatComponent_generated_h
#error "GaussianSplatComponent.generated.h already included, missing '#pragma once' in GaussianSplatComponent.h"
#endif
#define NANOGS_GaussianSplatComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UGaussianSplatAsset;

// ********** Begin Class UGaussianSplatComponent **************************************************
#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetSplatCount); \
	DECLARE_FUNCTION(execGetSplatAsset); \
	DECLARE_FUNCTION(execSetSplatAsset);


struct Z_Construct_UClass_UGaussianSplatComponent_Statics;
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatComponent(ETypeConstructPhase);

#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UGaussianSplatComponent_Statics; \
	friend NANOGS_API UClass* ::Z_Construct_UClass_UGaussianSplatComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UGaussianSplatComponent, UPrimitiveComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/NanoGS"), Z_Construct_UClass_UGaussianSplatComponent) \
	DECLARE_SERIALIZER(UGaussianSplatComponent)


#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGaussianSplatComponent(UGaussianSplatComponent&&) = delete; \
	UGaussianSplatComponent(const UGaussianSplatComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGaussianSplatComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGaussianSplatComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGaussianSplatComponent) \
	NO_API virtual ~UGaussianSplatComponent();


#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_23_PROLOG
#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_INCLASS_NO_PURE_DECLS \
	FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGaussianSplatComponent;

// ********** End Class UGaussianSplatComponent ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatComponent_h

// ********** Begin Enum EGaussianSplatRenderMode **************************************************
#define FOREACH_ENUM_EGAUSSIANSPLATRENDERMODE(op) \
	op(EGaussianSplatRenderMode::Gaussian) \
	op(EGaussianSplatRenderMode::PointCloud) 

enum class EGaussianSplatRenderMode : uint8;
template<> struct TIsUEnumClass<EGaussianSplatRenderMode> { enum { Value = true }; };
template<> UE_NODEBUG NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianSplatRenderMode>();
// ********** End Enum EGaussianSplatRenderMode ****************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
