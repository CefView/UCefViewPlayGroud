// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCefViewPlaygroundEditorTarget : TargetRules
{
    public UCefViewPlaygroundEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        ExtraModuleNames.Add("UCefViewPlayground");

#if UE_5_5_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
#elif UE_5_4_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
#elif UE_5_3_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
#elif UE_5_2_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V3;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
#elif UE_5_1_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
#elif UE_5_0_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V2;
#else
        throw new System.Exception("Unsupported UE Version");
#endif
    }
}
