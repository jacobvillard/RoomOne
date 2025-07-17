using UnrealBuildTool;
using System.IO;

public class ProceduralRopePlugin : ModuleRules
{
    public ProceduralRopePlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public")
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private")
            }
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "UMG", // Include UMG if your component needs it for any reason
				
			}
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
				// No private dependencies for the runtime module for now
			}
            );
    }
}
