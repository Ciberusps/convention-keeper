// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary)

UUE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary::UUE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary()
{
	RuleId = FName(TEXT("asset-naming-blueprint-function-library"));
	Description = FText::FromString(TEXT("Blueprint Function Library assets must use prefix BPFL_ (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blueprint-function-library"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.Blueprint"));
	Prefix = TEXT("BPFL_");
	UConventionKeeperRule_AssetNaming::RegisterBlueprintSpecialtyNativePath(TEXT("/Script/Engine.BlueprintFunctionLibrary"));
}

bool UUE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/Engine.BlueprintFunctionLibrary"));
}
