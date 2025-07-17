// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ProceduralRopeComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef PROCEDURALROPEPLUGIN_ProceduralRopeComponent_generated_h
#error "ProceduralRopeComponent.generated.h already included, missing '#pragma once' in ProceduralRopeComponent.h"
#endif
#define PROCEDURALROPEPLUGIN_ProceduralRopeComponent_generated_h

#define FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAttachEndToActor); \
	DECLARE_FUNCTION(execAttachStartToActor); \
	DECLARE_FUNCTION(execGenerateMesh); \
	DECLARE_FUNCTION(execGeneratePoints);


#define FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUProceduralRopeComponent(); \
	friend struct Z_Construct_UClass_UProceduralRopeComponent_Statics; \
public: \
	DECLARE_CLASS(UProceduralRopeComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProceduralRopePlugin"), NO_API) \
	DECLARE_SERIALIZER(UProceduralRopeComponent)


#define FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UProceduralRopeComponent(UProceduralRopeComponent&&); \
	UProceduralRopeComponent(const UProceduralRopeComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UProceduralRopeComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UProceduralRopeComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UProceduralRopeComponent) \
	NO_API virtual ~UProceduralRopeComponent();


#define FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_26_PROLOG
#define FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_INCLASS_NO_PURE_DECLS \
	FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROCEDURALROPEPLUGIN_API UClass* StaticClass<class UProceduralRopeComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h


#define FOREACH_ENUM_EROPEMESHAXIS(op) \
	op(ERopeMeshAxis::RMA_X) \
	op(ERopeMeshAxis::RMA_Y) \
	op(ERopeMeshAxis::RMA_Z) 

enum class ERopeMeshAxis : uint8;
template<> struct TIsUEnumClass<ERopeMeshAxis> { enum { Value = true }; };
template<> PROCEDURALROPEPLUGIN_API UEnum* StaticEnum<ERopeMeshAxis>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
