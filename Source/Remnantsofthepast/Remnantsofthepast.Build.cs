// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Remnantsofthepast : ModuleRules
{
	public Remnantsofthepast(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        { "Core",
          "CoreUObject",
          "Engine",
          "InputCore",
          "Niagara",
          "GameplayTasks",
          "NavigationSystem",
          "PhysicsCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[]
        {

          "Remnantsofthepast/Public/H_CoreTypes.h",

          "Remnantsofthepast/Public/AI/Tasks",
          "Remnantsofthepast/Public/AI/Servises",

        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
