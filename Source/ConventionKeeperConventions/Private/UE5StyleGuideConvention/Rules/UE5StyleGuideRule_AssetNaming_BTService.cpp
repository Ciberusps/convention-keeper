// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTService.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BTService)

UUE5StyleGuideRule_AssetNaming_BTService::UUE5StyleGuideRule_AssetNaming_BTService()
{
	RuleId = FName(TEXT("asset-naming-bt-service"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-bt-service"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	BlueprintParentClassPaths = { TEXT("/Script/AIModule.BTService_BlueprintBase") };
	Prefix = TEXT("BTService_");
}
