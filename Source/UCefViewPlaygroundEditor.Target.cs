// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCefViewPlaygroundEditorTarget : TargetRules
{
    public UCefViewPlaygroundEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        ExtraModuleNames.Add("UCefViewPlayground");

        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
    }
}
