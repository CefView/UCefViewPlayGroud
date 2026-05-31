// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCefViewPlaygroundEditorTarget : TargetRules
{
    public UCefViewPlaygroundEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        ExtraModuleNames.Add("UCefViewPlayground");

#if UE_5_1_OR_LATER
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
#elif UE_5_0_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V2;
#else
        throw new System.Exception("Unsupported UE Version");
#endif
    }
}
