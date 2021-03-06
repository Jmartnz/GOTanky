// Copyright Jmartnz 2017

using UnrealBuildTool;
using System.Collections.Generic;

public class GOTankyEditorTarget : TargetRules
{
	public GOTankyEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;

        bUseUnityBuild = false;
        bUsePCHFiles = false;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "GOTanky" } );
	}
}
