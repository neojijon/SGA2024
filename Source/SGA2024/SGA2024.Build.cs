// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SGA2024 : ModuleRules
{
	public SGA2024(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
