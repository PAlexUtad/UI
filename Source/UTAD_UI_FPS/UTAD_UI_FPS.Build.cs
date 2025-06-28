// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UTAD_UI_FPS : ModuleRules
{
	public UTAD_UI_FPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "SlateCore" });
	}
}
