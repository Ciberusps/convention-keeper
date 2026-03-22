// Pavel Penkov 2025 All Rights Reserved.

#include "EarendilConvention/Rules/EarendilConventionRule_AssetNaming_StateTree.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EarendilConventionRule_AssetNaming_StateTree)

UEarendilConventionRule_AssetNaming_StateTree::UEarendilConventionRule_AssetNaming_StateTree()
{
	RuleId = FName(TEXT("ec-asset-naming-state-tree"));
	Description = FText::FromString(TEXT("StateTree assets must use prefix ST_ (EarendilConvention)."));
	DescriptionKey = FName(TEXT("RuleDesc_ec-asset-naming-state-tree"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/StateTreeModule.StateTree"));
	AssetClassPaths.Add(TEXT("/Script/StateTreeEditorModule.StateTree"));
	Prefix = TEXT("ST_");
	PluginRequirements = { FName(TEXT("StateTree")) };
	bRequireAllPlugins = true;
}
