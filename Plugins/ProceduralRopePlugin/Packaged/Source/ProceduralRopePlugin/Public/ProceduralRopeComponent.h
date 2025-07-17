#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h" 
#include "Components/StaticMeshComponent.h" 
#include "Components/InstancedStaticMeshComponent.h" 

// Enum to define the primary axis of the static mesh for rope segments
UENUM(BlueprintType)
enum class ERopeMeshAxis : uint8
{
	RMA_X UMETA(DisplayName = "X Axis (Forward)"),
	RMA_Y UMETA(DisplayName = "Y Axis (Right)"),
	RMA_Z UMETA(DisplayName = "Z Axis (Up)")
};

// THIS MUST BE THE LAST INCLUDE IN THIS FILE!
#include "ProceduralRopeComponent.generated.h"

/**
 * @brief A component for simulating a dynamic rope with procedural generation.
 * Supports live updating, instanced meshes, and debug visualization.
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class PROCEDURALROPEPLUGIN_API UProceduralRopeComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UProceduralRopeComponent();

	/**
	 * @brief The world space start point of the rope.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Points")
	FVector StartPoint;

	/**
	 * @brief The world space end point of the rope.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Points")
	FVector EndPoint;

	/**
	* @brief The length of the rope.
	* If the distance between the start and end points is greater than Rope Length the rope will appear to be straight.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Physics")
	double RopeLength;

	/**
	* @brief The number of rope segments that should be calculated.
	* Higher values will decrease performance but improve visuals.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Physics", meta = (ClampMin = "2"))
	int32 NumberOfSegments;

	/**
	 * @brief The minimum time interval (in seconds) between automatic rope generation updates in the editor.
	 * Helps limit updates during rapid property adjustments and live ticking.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Performance", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float MinUpdateTimeInterval;

	/**
	* @brief Calculated based on distance between points and rope length
	* Hidden from user to reduce confusion.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Rope Physics")
	double SagMultiplier;

	/**
	* @brief Array of calculated points
	* Hidden from user to reduce confusion.
	*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Rope Physics")
	TArray<FVector> CalculatedPoints;

	/**
	 * @brief The Static Mesh to be used for visualizing each segment of the rope at runtime.
	 * Assign a mesh asset here in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals")
	TObjectPtr<UStaticMesh> RopeSegmentMesh;

	/**
	 * @brief Specifies which axis of the RopeSegmentMesh should align with the rope's direction.
	 * This is used for correct scaling and orientation of the instanced meshes.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals")
	ERopeMeshAxis MeshForwardAxis;

	/**
	 * @brief An amount (in Unreal Units) by which each mesh segment will overlap its neighbors.
	 * Use a small positive value to eliminate gaps. Too large a value will cause visible clipping.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MeshOverlapAmount;

	/**
	 * @brief If true, collision will be enabled for the instanced mesh components.
	 * Disabling collision can improve performance for purely visual ropes.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Physics")
	bool bEnableCollision;

	/**
	 * @brief If true, the rope will be visualized with debug lines in the editor viewport
	 * using the component visualizer. If false, it will use the Instanced Static Mesh.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals")
	bool bShowDebugLines;

	/**
	 * @brief Enables continuous updating of the rope in TickComponent when attached actors move.
	 * Disable for static ropes to save performance.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Performance")
	bool bEnableLiveUpdate;

	/**
	 * @brief Whether the rope should simulate dynamic sway (perpendicular oscillation).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals")
	bool bEnableRopeSway; // Enable/Disable Sway

	/**
	 * @brief How much the rope should sway if bEnableRopeSway is true.
	 * This value determines the amplitude of the sway.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals", meta = (ClampMin = "0.0", ClampMax = "1000.0", EditCondition = "bEnableRopeSway", EditConditionHides))
	float RopeSwayAmplitude; // Sway Amplitude, conditionally hidden

	/**
	 * @brief The frequency of the rope sway (how fast it oscillates) if bEnableRopeSway is true.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Visuals", meta = (ClampMin = "0.1", ClampMax = "10.0", EditCondition = "bEnableRopeSway", EditConditionHides))
	float RopeSwayFrequency; // Sway Frequency, conditionally hidden

	/**
	 * @brief The Instanced Static Mesh Component used to render the rope segments.
	 * Created dynamically within this component. Its visibility is controlled internally.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Rope Visuals")
	TObjectPtr<UInstancedStaticMeshComponent> InstancedMeshComponent;

protected:
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	float GetHorizontalDistance() const;
	float GetDroopValueAtAlpha(float Alpha) const;

public:
	UFUNCTION(BlueprintCallable, Category = "Rope Generation", CallInEditor)
	void GeneratePoints();

	UFUNCTION(BlueprintCallable, Category = "Rope Visuals")
	void GenerateMesh();

	// Attachment properties

	/**
	 * @brief The actor that the start point is attached to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Attachments")
	TObjectPtr<AActor> StartAttachedActor;

	/**
	 * @brief The actor that the end point is attached to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rope Attachments")
	TObjectPtr<AActor> EndAttachedActor;

	// Attachment functions - will directly set actor references
	UFUNCTION(BlueprintCallable, Category = "Rope Attachments")
	void AttachStartToActor(AActor* ParentActor);
	UFUNCTION(BlueprintCallable, Category = "Rope Attachments")
	void AttachEndToActor(AActor* ParentActor);

private:
	// These private helpers now check for valid attached actors directly (IsValid())
	void AttachStart();
	void AttachEnd();

	FTimerHandle DelayedGeneratePointsTimerHandle;
	float LastGeneratePointsTime; // Stores the timestamp of the last generation for TickComponent rate-limiting
};
