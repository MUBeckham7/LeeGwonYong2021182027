// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheDoldrums : ModuleRules
{
	public TheDoldrums(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]{ "TheDoldrums"});
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CinematicCamera" , "UMG" ,"GameplayCameras", "GeometryScriptingEditor" ,"MeshDescription", "MeshConversion" , "GeometryScriptingCore", "GeometryFramework" , "GeometryCore" , "Niagara","GameplayTags","CommonUI", "NarrativeInventory","NarrativeEquipment"});
        // "MeshDescription", "MeshConversion" , "GeometryCore" , "GeometryScriptingCore" ,"GeometryFramework","NarrativeInventory" , "GameplayTags"
        //PrivateDependencyModuleNames.AddRange(new string[] {});

        //Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
