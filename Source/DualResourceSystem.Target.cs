// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DualResourceSystemTarget : TargetRules
{
	public DualResourceSystemTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		WindowsPlatform.Compiler = WindowsCompiler.VisualStudio2022;
		ExtraModuleNames.Add("DualResourceSystem");
	}
}
