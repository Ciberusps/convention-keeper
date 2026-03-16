// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AIController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AIController)

UUE5StyleGuideRule_AssetNaming_AIController::UUE5StyleGuideRule_AssetNaming_AIController()
{
	RuleId = FName(TEXT("asset-naming-ai-controller"));
	Description = FText::FromString(TEXT("AI Controller (Blueprint) assets must use prefix AIC_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-ai-controller"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	BlueprintParentClassPaths = { TEXT("/Script/Engine.AIController") };
	Prefix = TEXT("AIC_");
}
