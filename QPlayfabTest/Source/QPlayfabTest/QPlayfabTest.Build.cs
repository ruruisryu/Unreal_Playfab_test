// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QPlayfabTest : ModuleRules
{
	public QPlayfabTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		// Playfab과 관련된 모듈 추가
		PrivateDependencyModuleNames.AddRange(new string[] { "PlayFab", "PlayFabCpp", "PlayFabCommon" });
	}
}
