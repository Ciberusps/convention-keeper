// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQuery.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_EnvQuery)

UUE5StyleGuideRule_AssetNaming_EnvQuery::UUE5StyleGuideRule_AssetNaming_EnvQuery()
{
	RuleId = FName(TEXT("asset-naming-env-query"));
	Description = FText::FromString(TEXT("Environment Query assets must use prefix EQS_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-env-query"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/AIModule.EnvQuery") };
	Prefix = TEXT("EQS_");
}
