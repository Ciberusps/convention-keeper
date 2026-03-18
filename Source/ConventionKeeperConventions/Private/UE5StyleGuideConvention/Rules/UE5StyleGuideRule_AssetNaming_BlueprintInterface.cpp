// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintInterface.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BlueprintInterface)

UUE5StyleGuideRule_AssetNaming_BlueprintInterface::UUE5StyleGuideRule_AssetNaming_BlueprintInterface()
{
	RuleId = FName(TEXT("asset-naming-blueprint-interface"));
	Description = FText::FromString(TEXT("Blueprint Interface assets must use prefix BPI_ (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blueprint-interface"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.Blueprint"));
	Prefix = TEXT("BPI_");
}

bool UUE5StyleGuideRule_AssetNaming_BlueprintInterface::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	if (!UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName))
	{
		return false;
	}
	return UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/Engine.BlueprintInterface")) ||
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/UnrealEd.BlueprintInterface"));
}
