// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_AssetNaming_StateTree.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CKConventionRule_AssetNaming_StateTree)

UCKConventionRule_AssetNaming_StateTree::UCKConventionRule_AssetNaming_StateTree()
{
	RuleId = FName(TEXT("ck-asset-naming-state-tree"));
	Description = FText::FromString(TEXT("StateTree assets must use prefix ST_ (CKConvention)."));
	DescriptionKey = FName(TEXT("RuleDesc_ck-asset-naming-state-tree"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/StateTreeModule.StateTree"));
	AssetClassPaths.Add(TEXT("/Script/StateTreeEditorModule.StateTree"));
	Prefix = TEXT("ST_");
	PluginRequirements = { FName(TEXT("StateTree")) };
	bRequireAllPlugins = true;
}
