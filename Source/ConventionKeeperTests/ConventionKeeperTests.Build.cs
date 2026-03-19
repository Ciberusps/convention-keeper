// Pavel Penkov 2025 All Rights Reserved.

using UnrealBuildTool;

public class ConventionKeeperTests : ModuleRules
{
	public ConventionKeeperTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AssetRegistry",
				"ConventionKeeperEditor",
				"ConventionKeeperConventions",
				"Projects",
				"UnrealEd",
			}
		);
	}
}
