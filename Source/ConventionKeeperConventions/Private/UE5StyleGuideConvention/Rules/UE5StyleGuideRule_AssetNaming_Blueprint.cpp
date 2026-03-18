// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Blueprint.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Blueprint)

UUE5StyleGuideRule_AssetNaming_Blueprint::UUE5StyleGuideRule_AssetNaming_Blueprint()
{
	RuleId = FName(TEXT("asset-naming-blueprint"));
	Description = FText::FromString(TEXT("Blueprint assets must use prefix BP_ or TBP_ (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blueprint"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.Blueprint"));
	AllowedPrefixes = { TEXT("BP_"), TEXT("TBP_") };
}

bool UUE5StyleGuideRule_AssetNaming_Blueprint::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return true;
	}
	FString NativeRoot;
	if (UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) && UConventionKeeperRule_AssetNaming::IsNativePathHandledBySpecialtyRule(NativeRoot))
	{
		return false;
	}
	return true;
}
