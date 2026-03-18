// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Structure.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Structure)

UUE5StyleGuideRule_AssetNaming_Structure::UUE5StyleGuideRule_AssetNaming_Structure()
{
	RuleId = FName(TEXT("asset-naming-structure"));
	Description = FText::FromString(TEXT("Blueprint Structure assets must use prefix F or S with no underscore (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-structure"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.UserDefinedStruct"));
	AllowedPrefixes = { TEXT("F"), TEXT("S") };
}
