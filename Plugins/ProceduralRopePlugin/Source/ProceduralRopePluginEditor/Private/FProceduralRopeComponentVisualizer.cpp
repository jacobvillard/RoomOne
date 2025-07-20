#include "FProceduralRopeComponentVisualizer.h"
#include "ProceduralRopeComponent.h" // Include your component's header (check path if different)
#include "SceneManagement.h"                 // For FPrimitiveDrawInterface and drawing functions
#include "Math/Vector.h"                     // For FVector
#include "Misc/CoreDelegates.h"              // For UE_LOG (useful for debugging)

FProceduralRopeComponentVisualizer::FProceduralRopeComponentVisualizer()
{
    // You can optionally log that the visualizer is constructed
    UE_LOG(LogTemp, Warning, TEXT("FProceduralRopeComponentVisualizer Constructed!"));
}

FProceduralRopeComponentVisualizer::~FProceduralRopeComponentVisualizer()
{
    // You can optionally log that the visualizer is destructed
    // UE_LOG(LogTemp, Warning, TEXT("FProceduralRopeComponentVisualizer Destructed!"));
}

void FProceduralRopeComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
    const UProceduralRopeComponent* ProceduralRopeComponent = Cast<UProceduralRopeComponent>(Component);
    if (ProceduralRopeComponent)
    {
        // Get the component's world transform for converting local points to world space
        const FTransform& ComponentTransform = ProceduralRopeComponent->GetComponentTransform();

        // Define drawing parameters
        FLinearColor RopeLineColor = FLinearColor::White; // Color for the debug rope line
        float RopeLineThickness = 2.0f; // Thickness for the debug rope line
        float EndPointSphereRadius = 15.0f; // Radius for the endpoint spheres
        int32 SphereSides = 16; // Number of segments for the spheres

        // --- Draw the curved rope debug lines ONLY IF bShowDebugLines is true ---
        if (ProceduralRopeComponent->bShowDebugLines) // NEW: Check the boolean property
        {
            const TArray<FVector>& PointsToDraw = ProceduralRopeComponent->CalculatedPoints;
            if (PointsToDraw.Num() > 1)
            {
                for (int32 i = 0; i < PointsToDraw.Num() - 1; ++i)
                {
                    // Transform points from component local space to world space before drawing
                    FVector WorldPoint1 = ComponentTransform.TransformPosition(PointsToDraw[i]);
                    FVector WorldPoint2 = ComponentTransform.TransformPosition(PointsToDraw[i + 1]);
                    PDI->DrawLine(WorldPoint1, WorldPoint2, RopeLineColor, SDPG_World, RopeLineThickness);
                }
                // UE_LOG(LogTemp, Log, TEXT("Visualizer Drawing Debug Lines."));
            }
            else if (PointsToDraw.Num() == 1)
            {
                PDI->DrawPoint(ComponentTransform.TransformPosition(PointsToDraw[0]), FLinearColor::Yellow, 20.0f, SDPG_World);
            }
        }
        else
        {
            // UE_LOG(LogTemp, Log, TEXT("Debug lines are disabled."));
        }

        //Drawing Points for start and end points
        PDI->DrawPoint(ComponentTransform.TransformPosition(ProceduralRopeComponent->StartPoint), FLinearColor::White, 10.0f, SDPG_World);
        PDI->DrawPoint(ComponentTransform.TransformPosition(ProceduralRopeComponent->EndPoint), FLinearColor::White, 10.0f, SDPG_World);

        UE_LOG(LogTemp, Warning, TEXT("Visualizer DrawVisualization called!"));
    }
}
