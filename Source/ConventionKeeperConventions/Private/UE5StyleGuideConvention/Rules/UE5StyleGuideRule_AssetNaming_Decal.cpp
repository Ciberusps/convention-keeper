// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Decal.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Decal)

UUE5StyleGuideRule_AssetNaming_Decal::UUE5StyleGuideRule_AssetNaming_Decal()
{
	RuleId = FName(TEXT("asset-naming-decal"));
	Description = FText::FromString(TEXT("Decal materials (Material / Material Instance, domain Deferred Decal) must use prefix M_ or MI_ and suffix _Decal (UE5 Style Guide 1.2.5)."));
	Description = FText::FromString(TEXT("Decal materials (Material / Material Instance, domain Deferred Decal) must use prefix M_ or MI_ and suffix _Decal (UE5 Style Guide 1.2.5)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-decal"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMaterial::StaticClass(), UMaterialInstanceConstant::StaticClass() };
	Suffix = TEXT("_Decal");
}

bool UUE5StyleGuideRule_AssetNaming_Decal::ShouldValidateAsset(const FAssetData& AssetData) const
{
	UObject* Loaded = AssetData.GetAsset();
	if (UMaterial* Material = Cast<UMaterial>(Loaded))
	{
		return Material->MaterialDomain == EMaterialDomain::MD_DeferredDecal;
	}
	if (UMaterialInstanceConstant* MIC = Cast<UMaterialInstanceConstant>(Loaded))
	{
		if (UMaterial* BaseMat = MIC->GetMaterial())
		{
			return BaseMat->MaterialDomain == EMaterialDomain::MD_DeferredDecal;
		}
	}
	return false;
}

bool UUE5StyleGuideRule_AssetNaming_Decal::GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const
{
	UObject* Loaded = AssetData.GetAsset();
	if (UMaterial* Material = Cast<UMaterial>(Loaded))
	{
		if (Material->MaterialDomain == EMaterialDomain::MD_DeferredDecal)
		{
			OutPrefix = TEXT("M_");
			return true;
		}
		return false;
	}
	if (UMaterialInstanceConstant* MIC = Cast<UMaterialInstanceConstant>(Loaded))
	{
		if (UMaterial* BaseMat = MIC->GetMaterial())
		{
			if (BaseMat->MaterialDomain == EMaterialDomain::MD_DeferredDecal)
			{
				OutPrefix = TEXT("MI_");
				return true;
			}
		}
		return false;
	}
	return false;
}
