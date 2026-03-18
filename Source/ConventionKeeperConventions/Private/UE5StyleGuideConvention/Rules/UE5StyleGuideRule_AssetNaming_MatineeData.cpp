// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MatineeData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MatineeData)

UUE5StyleGuideRule_AssetNaming_MatineeData::UUE5StyleGuideRule_AssetNaming_MatineeData()
{
	RuleId = FName(TEXT("asset-naming-matinee-data"));
	Description = FText::FromString(TEXT("Matinee Data assets must use prefix Matinee_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-matinee-data"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.InterpData"));
	Prefix = TEXT("Matinee_");
}
