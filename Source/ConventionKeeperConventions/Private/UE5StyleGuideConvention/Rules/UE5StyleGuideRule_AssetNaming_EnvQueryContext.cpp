// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQueryContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_EnvQueryContext)

UUE5StyleGuideRule_AssetNaming_EnvQueryContext::UUE5StyleGuideRule_AssetNaming_EnvQueryContext()
{
	RuleId = FName(TEXT("asset-naming-env-query-context"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-env-query-context"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	BlueprintParentClassPaths = { TEXT("/Script/AIModule.EnvQueryContext") };
	Prefix = TEXT("EQS_");
	Suffix = TEXT("Context");
}
