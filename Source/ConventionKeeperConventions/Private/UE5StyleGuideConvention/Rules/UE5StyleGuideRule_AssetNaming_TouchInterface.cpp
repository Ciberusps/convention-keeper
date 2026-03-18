// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_TouchInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_TouchInterface)

UUE5StyleGuideRule_AssetNaming_TouchInterface::UUE5StyleGuideRule_AssetNaming_TouchInterface()
{
	RuleId = FName(TEXT("asset-naming-touch-interface"));
	Description = FText::FromString(TEXT("Touch Interface Setup assets must use prefix TI_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-touch-interface"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.TouchInterface"));
	Prefix = TEXT("TI_");
}
