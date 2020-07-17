// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class AwesomeShooterTarget : TargetRules
{
	public AwesomeShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "AwesomeShooter" } );

        DefaultBuildSettings = BuildSettingsVersion.V2;
	}
}
