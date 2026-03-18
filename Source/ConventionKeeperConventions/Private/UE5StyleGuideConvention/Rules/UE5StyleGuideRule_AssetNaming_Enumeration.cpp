// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Enumeration.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Enumeration)

UUE5StyleGuideRule_AssetNaming_Enumeration::UUE5StyleGuideRule_AssetNaming_Enumeration()
{
	RuleId = FName(TEXT("asset-naming-enumeration"));
	Description = FText::FromString(TEXT("Blueprint Enumeration assets must use prefix E with no underscore (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-enumeration"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.UserDefinedEnum"));
	Prefix = TEXT("E");
}
