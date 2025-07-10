// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RoomOne : ModuleRules
{
	public RoomOne(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "OnlineSubsystem", "OnlineSubsystemEOS", "HTTP" });
	}
}
