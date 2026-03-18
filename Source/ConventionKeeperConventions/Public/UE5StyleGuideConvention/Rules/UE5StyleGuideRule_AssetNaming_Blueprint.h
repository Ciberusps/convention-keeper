// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"

class IAssetRegistry;
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_Blueprint.generated.h"

/** UE5 Style Guide 1.2.4: Generic Blueprint and Tutorial Blueprint assets must use prefix BP_ or TBP_. Excludes BPFL, BPI, BPML, Component, AIController, BT*, EnvQueryContext. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_Blueprint : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_Blueprint();

	virtual bool ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry = nullptr, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr) const override;
};
