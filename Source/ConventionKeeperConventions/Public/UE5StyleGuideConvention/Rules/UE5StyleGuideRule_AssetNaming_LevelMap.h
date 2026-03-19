// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_LevelMap.generated.h"

/** UE5 Style Guide 1.2.1 Most Common: Level/Map (World) assets may have optional suffix _P, _Audio, _Lighting, _Geo, _Gameplay. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_LevelMap : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_LevelMap();

	virtual bool GetCustomSuffixValidity(const FString& AssetName, const FString& UsedPrefix, bool& OutValid) const override;
	virtual FText GetCustomSuffixFailureMessage(const FString& AssetName, const FString& UsedPrefix) const override;
};
