// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetPlacement_SoundClass.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetPlacement_SoundClass)

UUE5StyleGuideRule_AssetPlacement_SoundClass::UUE5StyleGuideRule_AssetPlacement_SoundClass()
{
	RuleId = FName(TEXT("asset-placement-sound-class"));
	Description = FText::FromString(TEXT("Sound Class assets must be in a folder named SoundClasses (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-placement-sound-class"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.SoundClass"));
	RequiredPathSegment = TEXT("SoundClasses");
}
