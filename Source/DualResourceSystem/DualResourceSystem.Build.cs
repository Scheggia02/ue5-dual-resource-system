// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DualResourceSystem : ModuleRules
{
	public DualResourceSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"InputCore",
			"EnhancedInput"
		});
	}
}
