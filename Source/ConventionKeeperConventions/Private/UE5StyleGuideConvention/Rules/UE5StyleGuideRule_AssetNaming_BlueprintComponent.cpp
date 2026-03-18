// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintComponent.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BlueprintComponent)

UUE5StyleGuideRule_AssetNaming_BlueprintComponent::UUE5StyleGuideRule_AssetNaming_BlueprintComponent()
{
	RuleId = FName(TEXT("asset-naming-blueprint-component"));
	Description = FText::FromString(TEXT("Blueprint Component assets must use prefix BP_ and suffix Component (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blueprint-component"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.Blueprint"));
	Prefix = TEXT("BP_");
	Suffix = TEXT("Component");
	UConventionKeeperRule_AssetNaming::RegisterBlueprintSpecialtyNativePath(TEXT("/Script/Engine.ActorComponent"));
}

bool UUE5StyleGuideRule_AssetNaming_BlueprintComponent::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/Engine.ActorComponent"));
}
