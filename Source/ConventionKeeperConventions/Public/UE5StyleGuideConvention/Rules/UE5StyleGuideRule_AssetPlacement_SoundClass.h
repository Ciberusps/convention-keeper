// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetPlacement.h"
#include "UE5StyleGuideRule_AssetPlacement_SoundClass.generated.h"

/** UE5 Style Guide 1.2.10: Sound Class assets must be in a folder named SoundClasses (no prefix/suffix for the asset name). */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetPlacement_SoundClass : public UConventionKeeperRule_AssetPlacement
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetPlacement_SoundClass();
};
