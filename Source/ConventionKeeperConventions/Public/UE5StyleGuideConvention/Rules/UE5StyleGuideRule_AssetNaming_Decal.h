// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

class IAssetRegistry;
#include "UE5StyleGuideRule_AssetNaming_Decal.generated.h"

/** UE5 Style Guide 1.2.5: Decal (Material / Material Instance with domain Deferred Decal) must use prefix M_ or MI_ and suffix _Decal. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_Decal : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_Decal();

	virtual bool ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry = nullptr, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr) const override;
	virtual bool GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const override;
};
