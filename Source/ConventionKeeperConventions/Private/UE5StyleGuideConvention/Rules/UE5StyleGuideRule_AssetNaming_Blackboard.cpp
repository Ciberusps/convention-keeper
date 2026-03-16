// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Blackboard.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Blackboard)

UUE5StyleGuideRule_AssetNaming_Blackboard::UUE5StyleGuideRule_AssetNaming_Blackboard()
{
	RuleId = FName(TEXT("asset-naming-blackboard"));
	Description = FText::FromString(TEXT("Blackboard assets must use prefix BB_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blackboard"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/AIModule.BlackboardData") };
	Prefix = TEXT("BB_");
}
