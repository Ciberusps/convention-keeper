// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_Material.generated.h"

/** UE5 Style Guide 1.2.5: Material assets use M_; Post Process materials use PP_ (determined by MaterialDomain). */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_Material : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_Material();

	virtual bool GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const override;
};
