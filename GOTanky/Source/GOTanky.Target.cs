// Copyright Jmartnz 2017

using UnrealBuildTool;
using System.Collections.Generic;

public class GOTankyTarget : TargetRules
{
	public GOTankyTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
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
