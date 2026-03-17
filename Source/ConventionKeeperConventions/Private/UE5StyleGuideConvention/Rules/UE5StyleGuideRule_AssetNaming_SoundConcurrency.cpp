// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundConcurrency.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SoundConcurrency)

UUE5StyleGuideRule_AssetNaming_SoundConcurrency::UUE5StyleGuideRule_AssetNaming_SoundConcurrency()
{
	RuleId = FName(TEXT("asset-naming-sound-concurrency"));
	Description = FText::FromString(TEXT("Sound Concurrency assets must use suffix _SC (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sound-concurrency"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.SoundConcurrency"));
	Suffix = TEXT("_SC");
}
