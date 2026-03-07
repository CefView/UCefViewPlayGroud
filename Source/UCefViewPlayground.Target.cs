// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCefViewPlaygroundTarget : TargetRules
{
    public UCefViewPlaygroundTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        ExtraModuleNames.Add("UCefViewPlayground");

        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
    }
}
