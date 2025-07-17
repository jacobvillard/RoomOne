#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

class PROCEDURALROPEPLUGINEDITOR_API FProceduralRopeComponentVisualizer : public FComponentVisualizer
{
public:
    FProceduralRopeComponentVisualizer();
    virtual ~FProceduralRopeComponentVisualizer();

    virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;

    // Explicitly set to true to always show visualizer, even if component/actor is not selected
    virtual bool ShouldShowForUnselectedComponent(const UActorComponent* Component) { return true; }
};
