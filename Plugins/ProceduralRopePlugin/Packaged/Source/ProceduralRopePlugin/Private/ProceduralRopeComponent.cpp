#include "ProceduralRopeComponent.h"
#include "Kismet/KismetMathLibrary.h" 
#include "TimerManager.h" 
#include "Components/InstancedStaticMeshComponent.h" 
#include "Engine/StaticMesh.h" // Ensure UStaticMesh is defined

// Define a small constant to prevent division by zero or inverted ranges
#define KINDA_SMALL_NUMBER 1.e-4f

UProceduralRopeComponent::UProceduralRopeComponent()
{
    // Initialize ticks for the component
    PrimaryComponentTick.bCanEverTick = true;
    bTickInEditor = true;
    SetComponentTickEnabled(true);

    // Initialize default values for vectors
    StartPoint = FVector(0.0, 0.0, 0.0);
    EndPoint = FVector(350.0, 0.0, 0.0);

    // Initialize default values for floats
    NumberOfSegments = 30;
    RopeLength = 500.0;
    MinUpdateTimeInterval = 0.1f; // Used for both editor debounce and TickComponent rate-limiting
    MeshOverlapAmount = 1.0f;
    SagMultiplier = 0.0;
    RopeSwayAmplitude = 10.0f; // Default sway amount
    RopeSwayFrequency = 1.0f; // Default sway frequency

    // Initialize default values for object references
    StartAttachedActor = nullptr;
    EndAttachedActor = nullptr;
    RopeSegmentMesh = nullptr;

    // Initialize default values for enums
    MeshForwardAxis = ERopeMeshAxis::RMA_X;

    // Initialize default values for booleans
    bEnableCollision = false; // Default to no collision
    bShowDebugLines = false; // Default to showing instanced meshes
    bEnableLiveUpdate = true; // Enabled by default for live updates
    bEnableRopeSway = false; // Default to no sway

    // Create and setup InstancedStaticMeshComponent
    InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMeshComponent"));
    if (InstancedMeshComponent)
    {
        InstancedMeshComponent->SetupAttachment(this);
        InstancedMeshComponent->SetCanEverAffectNavigation(false);

        // Initial visibility/collision will be set by GenerateMesh() on first call
        InstancedMeshComponent->SetVisibility(false);
        InstancedMeshComponent->SetHiddenInGame(true);
        InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Default no collision
    }

    LastGeneratePointsTime = 0.0f; // Initialize last generation time
}

void UProceduralRopeComponent::OnRegister()
{
    Super::OnRegister();

    if (InstancedMeshComponent && RopeSegmentMesh)
    {
        InstancedMeshComponent->SetStaticMesh(RopeSegmentMesh);
    }

    GeneratePoints(); // Call GeneratePoints on registration for initial setup.
    // Set LastGeneratePointsTime after the initial generation to ensure first tick updates correctly
    if (GetWorld())
    {
        LastGeneratePointsTime = GetWorld()->GetTimeSeconds();
    }
}

void UProceduralRopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Only update if live update is enabled AND (at least one attached actor is valid OR sway is enabled)  
    // Sway needs consistent ticking even if not attached to an actor  
    if (bEnableLiveUpdate)
    {
        if (GetWorld())
        {
            float CurrentTime = GetWorld()->GetTimeSeconds();
            // Log live update status  

            // Only call GeneratePoints if enough time has passed since the last call.  
            if (CurrentTime - LastGeneratePointsTime >= MinUpdateTimeInterval)
            {
                GeneratePoints();
                LastGeneratePointsTime = CurrentTime; // Update timestamp  
            }
        }
    }
}

#if WITH_EDITOR 
void UProceduralRopeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.Property != nullptr)
    {
        FName PropertyName = PropertyChangedEvent.Property->GetFName();

        // Handle RopeSegmentMesh change specifically to update the ISMC's mesh
        if (PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, RopeSegmentMesh))
        {
            if (InstancedMeshComponent && RopeSegmentMesh)
            {
                InstancedMeshComponent->SetStaticMesh(RopeSegmentMesh);
            }
        }

        // Trigger GeneratePoints() (debounced) for relevant property changes
        // This includes all properties that directly affect the rope's shape, visual, or performance/update logic
        if (PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, StartPoint) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, EndPoint) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, NumberOfSegments) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, RopeLength) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, MinUpdateTimeInterval) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, bShowDebugLines) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, RopeSegmentMesh) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, bEnableLiveUpdate) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, StartAttachedActor) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, EndAttachedActor) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, MeshForwardAxis) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, MeshOverlapAmount) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, bEnableRopeSway) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, RopeSwayAmplitude) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, RopeSwayFrequency) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(UProceduralRopeComponent, bEnableCollision))
        {
            if (GetWorld())
            {
                GetWorld()->GetTimerManager().ClearTimer(DelayedGeneratePointsTimerHandle);
                GetWorld()->GetTimerManager().SetTimer(
                    DelayedGeneratePointsTimerHandle,
                    this,
                    &UProceduralRopeComponent::GeneratePoints,
                    MinUpdateTimeInterval,
                    false
                );
            }
            MarkRenderStateDirty();
        }
    }
}
#endif // WITH_EDITOR

// --- Attachment Functions ---
void UProceduralRopeComponent::AttachStartToActor(AActor* ParentActor)
{
    StartAttachedActor = ParentActor;
    GeneratePoints();
    MarkRenderStateDirty();
}

void UProceduralRopeComponent::AttachStart()
{
    if (IsValid(StartAttachedActor))
    {
        StartPoint = GetComponentTransform().InverseTransformPosition(StartAttachedActor->GetActorLocation());
    }
}

void UProceduralRopeComponent::AttachEndToActor(AActor* ParentActor)
{
    EndAttachedActor = ParentActor;
    GeneratePoints();
    MarkRenderStateDirty();
}

void UProceduralRopeComponent::AttachEnd()
{
    if (IsValid(EndAttachedActor))
    {
        EndPoint = GetComponentTransform().InverseTransformPosition(EndAttachedActor->GetActorLocation());
    }
}

// --- Sag Calculation Helpers ---

float UProceduralRopeComponent::GetHorizontalDistance() const
{
    FVector StartXY = FVector(StartPoint.X, StartPoint.Y, 0.0);
    FVector EndXY = FVector(EndPoint.X, EndPoint.Y, 0.0);
    return FVector::Dist(StartXY, EndXY);
}

float UProceduralRopeComponent::GetDroopValueAtAlpha(float Alpha) const
{
    float BaseParabolicDroop = 4.0 * Alpha * (1.0 - Alpha);
    return BaseParabolicDroop * SagMultiplier * RopeLength;
}

// --- Main Point Generation Function ---
void UProceduralRopeComponent::GeneratePoints()
{


    CalculatedPoints.Empty();

    if (NumberOfSegments <= 0)
    {
        if (InstancedMeshComponent) InstancedMeshComponent->ClearInstances();
        MarkRenderStateDirty();
        return;
    }

    int32 NumPoints = NumberOfSegments + 1;
    CalculatedPoints.Reserve(NumPoints);

    AttachStart();
    AttachEnd();

    float HorizontalDistance = GetHorizontalDistance();

    float MinRopeLengthForSag = HorizontalDistance;
    float MaxRopeLengthForSagConsideration = HorizontalDistance + 2000.0f;

    float TaughtThreshold = MinRopeLengthForSag;
    float SlackThreshold = FMath::Max(MinRopeLengthForSag + 10.0f, MaxRopeLengthForSagConsideration);

    SagMultiplier = FMath::GetMappedRangeValueClamped(
        FVector2f(TaughtThreshold, SlackThreshold),
        FVector2f(0.0f, 1.0f),
        RopeLength
    );
    SagMultiplier = FMath::Max(0.0, SagMultiplier);

    // Removed: RopeLength = FMath::Max(RopeLength, HorizontalDistance); 

    // Populate CalculatedPoints for visualizer (always)
    for (int32 i = 0; i < NumPoints; ++i)
    {
        float Alpha = static_cast<float>(i) / static_cast<float>(NumberOfSegments);
        FVector CurrentLERPPosition = FMath::Lerp(StartPoint, EndPoint, Alpha);
        float DroopAmount = GetDroopValueAtAlpha(Alpha);

        FVector FinalPointPosition = CurrentLERPPosition;
        FinalPointPosition.Z -= DroopAmount;

        // Apply rope sway only to intermediate points (not start and end points)
        if (bEnableRopeSway && GetWorld() && i > 0 && i < NumberOfSegments)
        {
            float Time = GetWorld()->GetTimeSeconds();
            // A simple sine wave perpendicular to the rope's horizontal direction
            FVector RopeHorizontalDir = (EndPoint - StartPoint);
            RopeHorizontalDir.Z = 0.0f;
            RopeHorizontalDir.Normalize();

            // Find a vector perpendicular to the horizontal rope direction (e.g., using cross product with UpVector)
            FVector PerpendicularSwayDir = FVector::CrossProduct(RopeHorizontalDir, FVector::UpVector);
            PerpendicularSwayDir.Normalize();

            // Calculate a parabolic weight that is 0 at ends and 1 in the middle
            // This ensures sway amplitude is smoothly reduced to zero at the attachment points.
            float SwayWeight = 4.0f * Alpha * (1.0f - Alpha);
            SwayWeight = SwayWeight * SagMultiplier;
            // Apply sine wave oscillation, scaled by SwayAmount and the new SwayWeight
            float SwayOffset = FMath::Sin(Time * RopeSwayFrequency + Alpha * PI) * RopeSwayAmplitude * SwayWeight;

            FinalPointPosition += PerpendicularSwayDir * SwayOffset;
        }

        CalculatedPoints.Add(FinalPointPosition);
    }

    // Call GenerateMesh after points are calculated
    GenerateMesh();

    MarkRenderStateDirty();
}

void UProceduralRopeComponent::GenerateMesh()
{
    // Clear old instances before adding new ones
    if (InstancedMeshComponent)
    {
        InstancedMeshComponent->ClearInstances();
        // Control InstancedMeshComponent visibility based on bShowDebugLines
        InstancedMeshComponent->SetVisibility(!bShowDebugLines); // Visible if debug lines are NOT shown
        InstancedMeshComponent->SetHiddenInGame(bShowDebugLines); // Hidden in game if debug lines ARE shown

        // Set collision enabled/disabled based on bEnableCollision
        if (bEnableCollision)
        {
            InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            InstancedMeshComponent->SetCollisionProfileName(TEXT("BlockAll")); // Set a default profile
        }
        else
        {
            InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            InstancedMeshComponent->SetCollisionProfileName(TEXT("NoCollision")); // Explicitly set to no collision
        }
    }

    // Only add instances if RopeSegmentMesh is valid AND debug lines are NOT shown
    if (InstancedMeshComponent && RopeSegmentMesh && !bShowDebugLines)
    {
        FVector MeshForwardVector;
        float MeshExtentComponent;

        // Determine the mesh's forward vector and the corresponding extent component based on the enum
        switch (MeshForwardAxis)
        {
        case ERopeMeshAxis::RMA_X:
            MeshForwardVector = FVector::ForwardVector; // X-axis
            MeshExtentComponent = RopeSegmentMesh->GetBounds().GetBox().GetExtent().X;
            break;
        case ERopeMeshAxis::RMA_Y:
            MeshForwardVector = FVector::RightVector; // Y-axis
            MeshExtentComponent = RopeSegmentMesh->GetBounds().GetBox().GetExtent().Y;
            break;
        case ERopeMeshAxis::RMA_Z:
            MeshForwardVector = FVector::UpVector; // Z-axis
            MeshExtentComponent = RopeSegmentMesh->GetBounds().GetBox().GetExtent().Z;
            break;
        default:
            MeshForwardVector = FVector::ForwardVector; // Default to X
            MeshExtentComponent = RopeSegmentMesh->GetBounds().GetBox().GetExtent().X;
            break;
        }

        for (int32 i = 0; i < NumberOfSegments; ++i) // Iterate for segments, not points
        {
            if (CalculatedPoints.IsValidIndex(i) && CalculatedPoints.IsValidIndex(i + 1))
            {
                FVector SegmentStart = CalculatedPoints[i];
                FVector SegmentEnd = CalculatedPoints[i + 1];

                FVector SegmentDirection = (SegmentEnd - SegmentStart);
                float ActualSegmentLength = SegmentDirection.Length();
                if (ActualSegmentLength < KINDA_SMALL_NUMBER) continue;

                SegmentDirection.Normalize();

                // Use the determined MeshForwardVector for rotation
                FQuat Rotation = FQuat::FindBetween(MeshForwardVector, SegmentDirection);

                FVector InstanceScale = FVector(1.0f, 1.0f, 1.0f);
                // Use the determined MeshExtentComponent for scaling, now adding overlap
                if (MeshExtentComponent > KINDA_SMALL_NUMBER)
                {
                    float TargetMeshLength = ActualSegmentLength + MeshOverlapAmount;

                    switch (MeshForwardAxis)
                    {
                    case ERopeMeshAxis::RMA_X:
                        InstanceScale.X = TargetMeshLength / (MeshExtentComponent * 2.0f);
                        break;
                    case ERopeMeshAxis::RMA_Y:
                        InstanceScale.Y = TargetMeshLength / (MeshExtentComponent * 2.0f);
                        break;
                    case ERopeMeshAxis::RMA_Z:
                        InstanceScale.Z = TargetMeshLength / (MeshExtentComponent * 2.0f);
                        break;
                    }
                }

                FTransform InstanceTransform;
                InstanceTransform.SetLocation(SegmentStart + (SegmentDirection * (ActualSegmentLength / 2.0f)));
                InstanceTransform.SetRotation(Rotation);
                InstanceTransform.SetScale3D(InstanceScale);

                InstancedMeshComponent->AddInstance(InstanceTransform);
            }
        }
    }
}
