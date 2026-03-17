// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Font.h"
#include "Engine/Font.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Font)

UUE5StyleGuideRule_AssetNaming_Font::UUE5StyleGuideRule_AssetNaming_Font()
{
	RuleId = FName(TEXT("asset-naming-font"));
	Description = FText::FromString(TEXT("Font assets must use prefix Font_ (UE5 Style Guide 1.2.11)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-font"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UFont::StaticClass() };
	Prefix = TEXT("Font_");
}
