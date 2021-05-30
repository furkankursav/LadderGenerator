// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LadderGenerator : ModuleRules
{
	public LadderGenerator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
