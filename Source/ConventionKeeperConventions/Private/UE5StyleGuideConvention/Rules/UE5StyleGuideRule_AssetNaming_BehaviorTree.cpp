// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BehaviorTree.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BehaviorTree)

UUE5StyleGuideRule_AssetNaming_BehaviorTree::UUE5StyleGuideRule_AssetNaming_BehaviorTree()
{
	RuleId = FName(TEXT("asset-naming-behavior-tree"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-behavior-tree"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/AIModule.BehaviorTree") };
	Prefix = TEXT("BT_");
}
