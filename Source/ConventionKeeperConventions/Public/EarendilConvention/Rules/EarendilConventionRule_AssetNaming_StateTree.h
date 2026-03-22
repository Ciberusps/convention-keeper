// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "EarendilConventionRule_AssetNaming_StateTree.generated.h"

/** EarendilConvention: StateTree assets must use prefix ST_. Active only when StateTree plugin is enabled. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UEarendilConventionRule_AssetNaming_StateTree : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UEarendilConventionRule_AssetNaming_StateTree();
};

