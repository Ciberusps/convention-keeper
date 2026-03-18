// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ObjectLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_ObjectLibrary)

UUE5StyleGuideRule_AssetNaming_ObjectLibrary::UUE5StyleGuideRule_AssetNaming_ObjectLibrary()
{
	RuleId = FName(TEXT("asset-naming-object-library"));
	Description = FText::FromString(TEXT("Object Library assets must use prefix OL_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-object-library"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.ObjectLibrary"));
	Prefix = TEXT("OL_");
}
