// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class FlappyUnrealBirdCPPEditorTarget : TargetRules
{
	public FlappyUnrealBirdCPPEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "FlappyUnrealBirdCPP" } );
	}
}
