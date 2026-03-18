// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"

class IAssetRegistry;
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_BlueprintComponent.generated.h"

/** UE5 Style Guide 1.2.4: Blueprint Component assets must use prefix BP_ and suffix Component. Includes direct and indirect (Blueprint child) heirs of ActorComponent. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_BlueprintComponent : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_BlueprintComponent();

	virtual bool ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry = nullptr, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr) const override;
};
