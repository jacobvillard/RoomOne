// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralRopePlugin/Public/ProceduralRopeComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProceduralRopeComponent() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
PROCEDURALROPEPLUGIN_API UClass* Z_Construct_UClass_UProceduralRopeComponent();
PROCEDURALROPEPLUGIN_API UClass* Z_Construct_UClass_UProceduralRopeComponent_NoRegister();
PROCEDURALROPEPLUGIN_API UEnum* Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis();
UPackage* Z_Construct_UPackage__Script_ProceduralRopePlugin();
// End Cross Module References

// Begin Enum ERopeMeshAxis
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ERopeMeshAxis;
static UEnum* ERopeMeshAxis_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ERopeMeshAxis.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ERopeMeshAxis.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis, (UObject*)Z_Construct_UPackage__Script_ProceduralRopePlugin(), TEXT("ERopeMeshAxis"));
	}
	return Z_Registration_Info_UEnum_ERopeMeshAxis.OuterSingleton;
}
template<> PROCEDURALROPEPLUGIN_API UEnum* StaticEnum<ERopeMeshAxis>()
{
	return ERopeMeshAxis_StaticEnum();
}
struct Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// Enum to define the primary axis of the static mesh for rope segments\n" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "RMA_X.DisplayName", "X Axis (Forward)" },
		{ "RMA_X.Name", "ERopeMeshAxis::RMA_X" },
		{ "RMA_Y.DisplayName", "Y Axis (Right)" },
		{ "RMA_Y.Name", "ERopeMeshAxis::RMA_Y" },
		{ "RMA_Z.DisplayName", "Z Axis (Up)" },
		{ "RMA_Z.Name", "ERopeMeshAxis::RMA_Z" },
		{ "ToolTip", "Enum to define the primary axis of the static mesh for rope segments" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ERopeMeshAxis::RMA_X", (int64)ERopeMeshAxis::RMA_X },
		{ "ERopeMeshAxis::RMA_Y", (int64)ERopeMeshAxis::RMA_Y },
		{ "ERopeMeshAxis::RMA_Z", (int64)ERopeMeshAxis::RMA_Z },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ProceduralRopePlugin,
	nullptr,
	"ERopeMeshAxis",
	"ERopeMeshAxis",
	Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis()
{
	if (!Z_Registration_Info_UEnum_ERopeMeshAxis.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ERopeMeshAxis.InnerSingleton, Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ERopeMeshAxis.InnerSingleton;
}
// End Enum ERopeMeshAxis

// Begin Class UProceduralRopeComponent Function AttachEndToActor
struct Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics
{
	struct ProceduralRopeComponent_eventAttachEndToActor_Parms
	{
		AActor* ParentActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Rope Attachments" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParentActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::NewProp_ParentActor = { "ParentActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ProceduralRopeComponent_eventAttachEndToActor_Parms, ParentActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::NewProp_ParentActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UProceduralRopeComponent, nullptr, "AttachEndToActor", nullptr, nullptr, Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::ProceduralRopeComponent_eventAttachEndToActor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::ProceduralRopeComponent_eventAttachEndToActor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UProceduralRopeComponent::execAttachEndToActor)
{
	P_GET_OBJECT(AActor,Z_Param_ParentActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AttachEndToActor(Z_Param_ParentActor);
	P_NATIVE_END;
}
// End Class UProceduralRopeComponent Function AttachEndToActor

// Begin Class UProceduralRopeComponent Function AttachStartToActor
struct Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics
{
	struct ProceduralRopeComponent_eventAttachStartToActor_Parms
	{
		AActor* ParentActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Rope Attachments" },
		{ "Comment", "// Attachment functions - will directly set actor references\n" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "Attachment functions - will directly set actor references" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParentActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::NewProp_ParentActor = { "ParentActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ProceduralRopeComponent_eventAttachStartToActor_Parms, ParentActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::NewProp_ParentActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UProceduralRopeComponent, nullptr, "AttachStartToActor", nullptr, nullptr, Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::ProceduralRopeComponent_eventAttachStartToActor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::ProceduralRopeComponent_eventAttachStartToActor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UProceduralRopeComponent::execAttachStartToActor)
{
	P_GET_OBJECT(AActor,Z_Param_ParentActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AttachStartToActor(Z_Param_ParentActor);
	P_NATIVE_END;
}
// End Class UProceduralRopeComponent Function AttachStartToActor

// Begin Class UProceduralRopeComponent Function GenerateMesh
struct Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Rope Visuals" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UProceduralRopeComponent, nullptr, "GenerateMesh", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh_Statics::Function_MetaDataParams), Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UProceduralRopeComponent::execGenerateMesh)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->GenerateMesh();
	P_NATIVE_END;
}
// End Class UProceduralRopeComponent Function GenerateMesh

// Begin Class UProceduralRopeComponent Function GeneratePoints
struct Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Rope Generation" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UProceduralRopeComponent, nullptr, "GeneratePoints", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints_Statics::Function_MetaDataParams), Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UProceduralRopeComponent::execGeneratePoints)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->GeneratePoints();
	P_NATIVE_END;
}
// End Class UProceduralRopeComponent Function GeneratePoints

// Begin Class UProceduralRopeComponent
void UProceduralRopeComponent::StaticRegisterNativesUProceduralRopeComponent()
{
	UClass* Class = UProceduralRopeComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AttachEndToActor", &UProceduralRopeComponent::execAttachEndToActor },
		{ "AttachStartToActor", &UProceduralRopeComponent::execAttachStartToActor },
		{ "GenerateMesh", &UProceduralRopeComponent::execGenerateMesh },
		{ "GeneratePoints", &UProceduralRopeComponent::execGeneratePoints },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UProceduralRopeComponent);
UClass* Z_Construct_UClass_UProceduralRopeComponent_NoRegister()
{
	return UProceduralRopeComponent::StaticClass();
}
struct Z_Construct_UClass_UProceduralRopeComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * @brief A component for simulating a dynamic rope with procedural generation.\n * Supports live updating, instanced meshes, and debug visualization.\n */" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "ProceduralRopeComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief A component for simulating a dynamic rope with procedural generation.\nSupports live updating, instanced meshes, and debug visualization." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartPoint_MetaData[] = {
		{ "Category", "Rope Points" },
		{ "Comment", "/**\n\x09 * @brief The world space start point of the rope.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The world space start point of the rope." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EndPoint_MetaData[] = {
		{ "Category", "Rope Points" },
		{ "Comment", "/**\n\x09 * @brief The world space end point of the rope.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The world space end point of the rope." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RopeLength_MetaData[] = {
		{ "Category", "Rope Physics" },
		{ "Comment", "/**\n\x09* @brief The length of the rope.\n\x09* If the distance between the start and end points is greater than Rope Length the rope will appear to be straight.\n\x09*/" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The length of the rope.\nIf the distance between the start and end points is greater than Rope Length the rope will appear to be straight." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfSegments_MetaData[] = {
		{ "Category", "Rope Physics" },
		{ "ClampMin", "2" },
		{ "Comment", "/**\n\x09* @brief The number of rope segments that should be calculated.\n\x09* Higher values will decrease performance but improve visuals.\n\x09*/" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The number of rope segments that should be calculated.\nHigher values will decrease performance but improve visuals." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinUpdateTimeInterval_MetaData[] = {
		{ "Category", "Rope Performance" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.01" },
		{ "Comment", "/**\n\x09 * @brief The minimum time interval (in seconds) between automatic rope generation updates in the editor.\n\x09 * Helps limit updates during rapid property adjustments and live ticking.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The minimum time interval (in seconds) between automatic rope generation updates in the editor.\nHelps limit updates during rapid property adjustments and live ticking." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SagMultiplier_MetaData[] = {
		{ "Category", "Rope Physics" },
		{ "Comment", "/**\n\x09* @brief Calculated based on distance between points and rope length\n\x09* Hidden from user to reduce confusion.\n\x09*/" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief Calculated based on distance between points and rope length\nHidden from user to reduce confusion." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CalculatedPoints_MetaData[] = {
		{ "Category", "Rope Physics" },
		{ "Comment", "/**\n\x09* @brief Array of calculated points\n\x09* Hidden from user to reduce confusion.\n\x09*/" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief Array of calculated points\nHidden from user to reduce confusion." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RopeSegmentMesh_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "Comment", "/**\n\x09 * @brief The Static Mesh to be used for visualizing each segment of the rope at runtime.\n\x09 * Assign a mesh asset here in the editor.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The Static Mesh to be used for visualizing each segment of the rope at runtime.\nAssign a mesh asset here in the editor." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshForwardAxis_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "Comment", "/**\n\x09 * @brief Specifies which axis of the RopeSegmentMesh should align with the rope's direction.\n\x09 * This is used for correct scaling and orientation of the instanced meshes.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief Specifies which axis of the RopeSegmentMesh should align with the rope's direction.\nThis is used for correct scaling and orientation of the instanced meshes." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshOverlapAmount_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "ClampMax", "100.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/**\n\x09 * @brief An amount (in Unreal Units) by which each mesh segment will overlap its neighbors.\n\x09 * Use a small positive value to eliminate gaps. Too large a value will cause visible clipping.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief An amount (in Unreal Units) by which each mesh segment will overlap its neighbors.\nUse a small positive value to eliminate gaps. Too large a value will cause visible clipping." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableCollision_MetaData[] = {
		{ "Category", "Rope Physics" },
		{ "Comment", "/**\n\x09 * @brief If true, collision will be enabled for the instanced mesh components.\n\x09 * Disabling collision can improve performance for purely visual ropes.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief If true, collision will be enabled for the instanced mesh components.\nDisabling collision can improve performance for purely visual ropes." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowDebugLines_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "Comment", "/**\n\x09 * @brief If true, the rope will be visualized with debug lines in the editor viewport\n\x09 * using the component visualizer. If false, it will use the Instanced Static Mesh.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief If true, the rope will be visualized with debug lines in the editor viewport\nusing the component visualizer. If false, it will use the Instanced Static Mesh." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableLiveUpdate_MetaData[] = {
		{ "Category", "Rope Performance" },
		{ "Comment", "/**\n\x09 * @brief Enables continuous updating of the rope in TickComponent when attached actors move.\n\x09 * Disable for static ropes to save performance.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief Enables continuous updating of the rope in TickComponent when attached actors move.\nDisable for static ropes to save performance." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableRopeSway_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "Comment", "/**\n\x09 * @brief Whether the rope should simulate dynamic sway (perpendicular oscillation).\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief Whether the rope should simulate dynamic sway (perpendicular oscillation)." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RopeSwayAmplitude_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "ClampMax", "1000.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/**\n\x09 * @brief How much the rope should sway if bEnableRopeSway is true.\n\x09 * This value determines the amplitude of the sway.\n\x09 */" },
		{ "EditCondition", "bEnableRopeSway" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief How much the rope should sway if bEnableRopeSway is true.\nThis value determines the amplitude of the sway." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RopeSwayFrequency_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
		{ "Comment", "/**\n\x09 * @brief The frequency of the rope sway (how fast it oscillates) if bEnableRopeSway is true.\n\x09 */" },
		{ "EditCondition", "bEnableRopeSway" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The frequency of the rope sway (how fast it oscillates) if bEnableRopeSway is true." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InstancedMeshComponent_MetaData[] = {
		{ "Category", "Rope Visuals" },
		{ "Comment", "/**\n\x09 * @brief The Instanced Static Mesh Component used to render the rope segments.\n\x09 * Created dynamically within this component. Its visibility is controlled internally.\n\x09 */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The Instanced Static Mesh Component used to render the rope segments.\nCreated dynamically within this component. Its visibility is controlled internally." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartAttachedActor_MetaData[] = {
		{ "Category", "Rope Attachments" },
		{ "Comment", "/**\n\x09 * @brief The actor that the start point is attached to.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The actor that the start point is attached to." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EndAttachedActor_MetaData[] = {
		{ "Category", "Rope Attachments" },
		{ "Comment", "/**\n\x09 * @brief The actor that the end point is attached to.\n\x09 */" },
		{ "ModuleRelativePath", "Public/ProceduralRopeComponent.h" },
		{ "ToolTip", "@brief The actor that the end point is attached to." },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_StartPoint;
	static const UECodeGen_Private::FStructPropertyParams NewProp_EndPoint;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_RopeLength;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumberOfSegments;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinUpdateTimeInterval;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_SagMultiplier;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CalculatedPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CalculatedPoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RopeSegmentMesh;
	static const UECodeGen_Private::FBytePropertyParams NewProp_MeshForwardAxis_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_MeshForwardAxis;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeshOverlapAmount;
	static void NewProp_bEnableCollision_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableCollision;
	static void NewProp_bShowDebugLines_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowDebugLines;
	static void NewProp_bEnableLiveUpdate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableLiveUpdate;
	static void NewProp_bEnableRopeSway_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableRopeSway;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RopeSwayAmplitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RopeSwayFrequency;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InstancedMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StartAttachedActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EndAttachedActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UProceduralRopeComponent_AttachEndToActor, "AttachEndToActor" }, // 391272287
		{ &Z_Construct_UFunction_UProceduralRopeComponent_AttachStartToActor, "AttachStartToActor" }, // 600280106
		{ &Z_Construct_UFunction_UProceduralRopeComponent_GenerateMesh, "GenerateMesh" }, // 3485787849
		{ &Z_Construct_UFunction_UProceduralRopeComponent_GeneratePoints, "GeneratePoints" }, // 1975098772
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UProceduralRopeComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_StartPoint = { "StartPoint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, StartPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartPoint_MetaData), NewProp_StartPoint_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_EndPoint = { "EndPoint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, EndPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EndPoint_MetaData), NewProp_EndPoint_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeLength = { "RopeLength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, RopeLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RopeLength_MetaData), NewProp_RopeLength_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_NumberOfSegments = { "NumberOfSegments", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, NumberOfSegments), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumberOfSegments_MetaData), NewProp_NumberOfSegments_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MinUpdateTimeInterval = { "MinUpdateTimeInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, MinUpdateTimeInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinUpdateTimeInterval_MetaData), NewProp_MinUpdateTimeInterval_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_SagMultiplier = { "SagMultiplier", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, SagMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SagMultiplier_MetaData), NewProp_SagMultiplier_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_CalculatedPoints_Inner = { "CalculatedPoints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_CalculatedPoints = { "CalculatedPoints", nullptr, (EPropertyFlags)0x0010000000002014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, CalculatedPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CalculatedPoints_MetaData), NewProp_CalculatedPoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeSegmentMesh = { "RopeSegmentMesh", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, RopeSegmentMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RopeSegmentMesh_MetaData), NewProp_RopeSegmentMesh_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MeshForwardAxis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MeshForwardAxis = { "MeshForwardAxis", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, MeshForwardAxis), Z_Construct_UEnum_ProceduralRopePlugin_ERopeMeshAxis, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshForwardAxis_MetaData), NewProp_MeshForwardAxis_MetaData) }; // 2457353774
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MeshOverlapAmount = { "MeshOverlapAmount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, MeshOverlapAmount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshOverlapAmount_MetaData), NewProp_MeshOverlapAmount_MetaData) };
void Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableCollision_SetBit(void* Obj)
{
	((UProceduralRopeComponent*)Obj)->bEnableCollision = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableCollision = { "bEnableCollision", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UProceduralRopeComponent), &Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableCollision_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableCollision_MetaData), NewProp_bEnableCollision_MetaData) };
void Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bShowDebugLines_SetBit(void* Obj)
{
	((UProceduralRopeComponent*)Obj)->bShowDebugLines = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bShowDebugLines = { "bShowDebugLines", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UProceduralRopeComponent), &Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bShowDebugLines_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowDebugLines_MetaData), NewProp_bShowDebugLines_MetaData) };
void Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableLiveUpdate_SetBit(void* Obj)
{
	((UProceduralRopeComponent*)Obj)->bEnableLiveUpdate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableLiveUpdate = { "bEnableLiveUpdate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UProceduralRopeComponent), &Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableLiveUpdate_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableLiveUpdate_MetaData), NewProp_bEnableLiveUpdate_MetaData) };
void Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableRopeSway_SetBit(void* Obj)
{
	((UProceduralRopeComponent*)Obj)->bEnableRopeSway = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableRopeSway = { "bEnableRopeSway", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UProceduralRopeComponent), &Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableRopeSway_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableRopeSway_MetaData), NewProp_bEnableRopeSway_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeSwayAmplitude = { "RopeSwayAmplitude", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, RopeSwayAmplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RopeSwayAmplitude_MetaData), NewProp_RopeSwayAmplitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeSwayFrequency = { "RopeSwayFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, RopeSwayFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RopeSwayFrequency_MetaData), NewProp_RopeSwayFrequency_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_InstancedMeshComponent = { "InstancedMeshComponent", nullptr, (EPropertyFlags)0x011400000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, InstancedMeshComponent), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InstancedMeshComponent_MetaData), NewProp_InstancedMeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_StartAttachedActor = { "StartAttachedActor", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, StartAttachedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartAttachedActor_MetaData), NewProp_StartAttachedActor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_EndAttachedActor = { "EndAttachedActor", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProceduralRopeComponent, EndAttachedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EndAttachedActor_MetaData), NewProp_EndAttachedActor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UProceduralRopeComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_StartPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_EndPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_NumberOfSegments,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MinUpdateTimeInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_SagMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_CalculatedPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_CalculatedPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeSegmentMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MeshForwardAxis_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MeshForwardAxis,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_MeshOverlapAmount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bShowDebugLines,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableLiveUpdate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_bEnableRopeSway,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeSwayAmplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_RopeSwayFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_InstancedMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_StartAttachedActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProceduralRopeComponent_Statics::NewProp_EndAttachedActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProceduralRopeComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UProceduralRopeComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralRopePlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProceduralRopeComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UProceduralRopeComponent_Statics::ClassParams = {
	&UProceduralRopeComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UProceduralRopeComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UProceduralRopeComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UProceduralRopeComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UProceduralRopeComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UProceduralRopeComponent()
{
	if (!Z_Registration_Info_UClass_UProceduralRopeComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UProceduralRopeComponent.OuterSingleton, Z_Construct_UClass_UProceduralRopeComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UProceduralRopeComponent.OuterSingleton;
}
template<> PROCEDURALROPEPLUGIN_API UClass* StaticClass<UProceduralRopeComponent>()
{
	return UProceduralRopeComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UProceduralRopeComponent);
UProceduralRopeComponent::~UProceduralRopeComponent() {}
// End Class UProceduralRopeComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ERopeMeshAxis_StaticEnum, TEXT("ERopeMeshAxis"), &Z_Registration_Info_UEnum_ERopeMeshAxis, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2457353774U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UProceduralRopeComponent, UProceduralRopeComponent::StaticClass, TEXT("UProceduralRopeComponent"), &Z_Registration_Info_UClass_UProceduralRopeComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UProceduralRopeComponent), 2689057579U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_417469753(TEXT("/Script/ProceduralRopePlugin"),
	Z_CompiledInDeferFile_FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Files_UnrealEnginePlugins_ProceduralRopePlugin_Packaged_HostProject_Plugins_ProceduralRopePlugin_Source_ProceduralRopePlugin_Public_ProceduralRopeComponent_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
