// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BehaviorTree.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BehaviorTree)

UUE5StyleGuideRule_AssetNaming_BehaviorTree::UUE5StyleGuideRule_AssetNaming_BehaviorTree()
{
	RuleId = FName(TEXT("asset-naming-behavior-tree"));
	Description = FText::FromString(TEXT("Behavior Tree assets must use prefix BT_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-behavior-tree"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/AIModule.BehaviorTree") };
	Prefix = TEXT("BT_");
}
