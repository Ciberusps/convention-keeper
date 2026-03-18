// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DataTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_DataTable)

UUE5StyleGuideRule_AssetNaming_DataTable::UUE5StyleGuideRule_AssetNaming_DataTable()
{
	RuleId = FName(TEXT("asset-naming-data-table"));
	Description = FText::FromString(TEXT("Data Table assets must use prefix DT_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-data-table"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.DataTable"));
	Prefix = TEXT("DT_");
}
