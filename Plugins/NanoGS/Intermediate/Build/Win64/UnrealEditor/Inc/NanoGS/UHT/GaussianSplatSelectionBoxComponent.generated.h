// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GaussianSplatSelectionBoxComponent.h"

#ifdef NANOGS_GaussianSplatSelectionBoxComponent_generated_h
#error "GaussianSplatSelectionBoxComponent.generated.h already included, missing '#pragma once' in GaussianSplatSelectionBoxComponent.h"
#endif
#define NANOGS_GaussianSplatSelectionBoxComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UGaussianSplatSelectionBoxComponent **************************************
struct Z_Construct_UClass_UGaussianSplatSelectionBoxComponent_Statics;
NANOGS_API UClass* Z_Construct_UClass_UGaussianSplatSelectionBoxComponent(ETypeConstructPhase);

#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h_51_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UGaussianSplatSelectionBoxComponent_Statics; \
	friend NANOGS_API UClass* ::Z_Construct_UClass_UGaussianSplatSelectionBoxComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UGaussianSplatSelectionBoxComponent, UBoxComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/NanoGS"), Z_Construct_UClass_UGaussianSplatSelectionBoxComponent) \
	DECLARE_SERIALIZER(UGaussianSplatSelectionBoxComponent)


#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h_51_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGaussianSplatSelectionBoxComponent(UGaussianSplatSelectionBoxComponent&&) = delete; \
	UGaussianSplatSelectionBoxComponent(const UGaussianSplatSelectionBoxComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGaussianSplatSelectionBoxComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGaussianSplatSelectionBoxComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGaussianSplatSelectionBoxComponent) \
	NO_API virtual ~UGaussianSplatSelectionBoxComponent();


#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h_48_PROLOG
#define FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h_51_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h_51_INCLASS_NO_PURE_DECLS \
	FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h_51_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGaussianSplatSelectionBoxComponent;

// ********** End Class UGaussianSplatSelectionBoxComponent ****************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_34670_Documents_Unreal_Projects_DreamServiceCenter_5_8_Plugins_NanoGS_Source_NanoGS_Public_GaussianSplatSelectionBoxComponent_h

// ********** Begin Enum EGaussianSplatSelectionBoxMode ********************************************
#define FOREACH_ENUM_EGAUSSIANSPLATSELECTIONBOXMODE(op) \
	op(EGaussianSplatSelectionBoxMode::Cull) \
	op(EGaussianSplatSelectionBoxMode::Keep) 

enum class EGaussianSplatSelectionBoxMode : uint8;
template<> struct TIsUEnumClass<EGaussianSplatSelectionBoxMode> { enum { Value = true }; };
template<> UE_NODEBUG NANOGS_NON_ATTRIBUTED_API UEnum* StaticEnum<EGaussianSplatSelectionBoxMode>();
// ********** End Enum EGaussianSplatSelectionBoxMode **********************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
