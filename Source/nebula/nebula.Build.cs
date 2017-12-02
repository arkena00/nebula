// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class nebula : ModuleRules
{
	public nebula(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "Http", "Json", "JsonUtilities" });

        // ndb
        string ndb_path = "C:/Projet/nk/ndb";

        PublicIncludePaths.Add(ndb_path + "/include");
        PublicIncludePaths.Add(ndb_path + "/extlib/include/libmongoc-1.0");
        PublicIncludePaths.Add(ndb_path + "/extlib/include/libbson-1.0");
        PublicAdditionalLibraries.Add(ndb_path + "/extlib/lib/mongoc-static-1.0.lib");
        PublicAdditionalLibraries.Add(ndb_path + "/extlib/lib/bson-static-1.0.lib");

        PublicAdditionalLibraries.Add("ws2_32.lib");
        PublicAdditionalLibraries.Add("Secur32.lib");
        PublicAdditionalLibraries.Add("Crypt32.lib");
        PublicAdditionalLibraries.Add("BCrypt.lib");
    }
}
