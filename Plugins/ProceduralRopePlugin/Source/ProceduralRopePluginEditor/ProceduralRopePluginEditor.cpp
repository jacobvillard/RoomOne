#include "ProceduralRopePluginEditor.h"
#include "FProceduralRopeComponentVisualizer.h" // Your component visualizer header
// IMPORTANT: Include your component header from the runtime plugin module using its full path
#include "ProceduralRopeComponent.h"
#include "UnrealEdGlobals.h"            // For GUnrealEd
#include "Editor/UnrealEdEngine.h"      // For UUnrealEdEngine
#include "Misc/CoreDelegates.h"         // For UE_LOG

// This macro is essential for Unreal Engine to discover and load your module.
IMPLEMENT_MODULE(FProceduralRopePluginEditorModule, ProceduralRopePluginEditor)

// Static shared pointer to hold our visualizer instance
TSharedPtr<FProceduralRopeComponentVisualizer> ProceduralRopeVisualizer;

void FProceduralRopePluginEditorModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("PLUGIN: ProceduralRopePluginEditor Module StartupModule Fired!"));

    if (GUnrealEd)
    {
        ProceduralRopeVisualizer = MakeShareable(new FProceduralRopeComponentVisualizer());
        // Register the visualizer for the UProceduralRopeComponent class
        GUnrealEd->RegisterComponentVisualizer(UProceduralRopeComponent::StaticClass()->GetFName(), ProceduralRopeVisualizer);
        UE_LOG(LogTemp, Warning, TEXT("PLUGIN: UProceduralRopeComponent Visualizer Registered."));
    }
}

void FProceduralRopePluginEditorModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("PLUGIN: ProceduralRopePluginEditor Module ShutdownModule Fired!"));
    if (GUnrealEd && ProceduralRopeVisualizer.IsValid())
    {
        GUnrealEd->UnregisterComponentVisualizer(UProceduralRopeComponent::StaticClass()->GetFName());
        ProceduralRopeVisualizer.Reset();
    }
}
