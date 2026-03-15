// Pavel Penkov 2025 All Rights Reserved.

using UnrealBuildTool;

public class ConventionKeeperConventions : ModuleRules
{
	public ConventionKeeperConventions(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"LevelSequence",
				"Paper2D",
				"ControlRig",
				"ControlRigDeveloper",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"ConventionKeeperEditor",
			}
		);
	}
}
