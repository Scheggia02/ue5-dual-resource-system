// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DualResourceSystemEditorTarget : TargetRules
{
	public DualResourceSystemEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		WindowsPlatform.Compiler = WindowsCompiler.VisualStudio2022;
		ExtraModuleNames.Add("DualResourceSystem");
	}
}
