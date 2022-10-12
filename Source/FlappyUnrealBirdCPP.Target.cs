// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class FlappyUnrealBirdCPPTarget : TargetRules
{
	public FlappyUnrealBirdCPPTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		//mejorar tiempos de compilado
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
		//-----------------------------

        ExtraModuleNames.AddRange( new string[] { "FlappyUnrealBirdCPP" } );
	}
}
