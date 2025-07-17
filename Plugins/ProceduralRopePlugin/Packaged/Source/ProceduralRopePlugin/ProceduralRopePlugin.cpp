#include "ProceduralRopePlugin.h"
#include "Modules/ModuleManager.h"
#include "Misc/CoreDelegates.h" // For UE_LOG

// This macro is essential for Unreal Engine to discover and load your module.
IMPLEMENT_MODULE(FProceduralRopePluginModule, ProceduralRopePlugin)

void FProceduralRopePluginModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("PLUGIN: ProceduralRopePlugin Module StartupModule Fired!"));
}

void FProceduralRopePluginModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("PLUGIN: ProceduralRopePlugin Module ShutdownModule Fired!"));
}
