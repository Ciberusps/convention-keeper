// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQuery.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_EnvQuery)

UUE5StyleGuideRule_AssetNaming_EnvQuery::UUE5StyleGuideRule_AssetNaming_EnvQuery()
{
	RuleId = FName(TEXT("asset-naming-env-query"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-env-query"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/AIModule.EnvQuery") };
	Prefix = TEXT("EQS_");
}
