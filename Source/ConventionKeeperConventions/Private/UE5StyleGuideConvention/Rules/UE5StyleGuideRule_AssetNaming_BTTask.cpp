// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTTask.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BTTask)

UUE5StyleGuideRule_AssetNaming_BTTask::UUE5StyleGuideRule_AssetNaming_BTTask()
{
	RuleId = FName(TEXT("asset-naming-bt-task"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-bt-task"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	BlueprintParentClassPaths = { TEXT("/Script/AIModule.BTTask_BlueprintBase") };
	Prefix = TEXT("BTTask_");
}
