// Pavel Penkov 2025 All Rights Reserved.

using UnrealBuildTool;

public class ConventionKeeperValidationEditor : ModuleRules
{
	public ConventionKeeperValidationEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"ConventionKeeperEditor",
			"DataValidation",
			"StateTreeModule",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UnrealEd",
			"AssetRegistry",
		});
	}
}
