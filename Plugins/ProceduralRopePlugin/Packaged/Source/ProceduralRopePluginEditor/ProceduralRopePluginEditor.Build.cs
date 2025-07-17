using UnrealBuildTool;
using System.IO;

public class ProceduralRopePluginEditor : ModuleRules
{
    public ProceduralRopePluginEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ModuleDirectory, "Private")
            }
            );

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public") // FIXED: Use Path.Combine with ModuleDirectory
			}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "ProceduralRopePlugin" // IMPORTANT: This editor module depends on your runtime plugin module
			}
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",              // Core editor functionality
                "ComponentVisualizers",  // For component visualizers themselves
                "RHI",
                "RenderCore",
                "Projects",
                "Kismet",
                "ToolMenus",
                "PropertyEditor",
                "EditorStyle",
                "ApplicationCore"
            }
            );
    }
}
