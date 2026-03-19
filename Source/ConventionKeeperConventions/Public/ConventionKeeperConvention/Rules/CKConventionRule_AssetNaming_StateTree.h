// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "CKConventionRule_AssetNaming_StateTree.generated.h"

/** CKConvention: StateTree assets must use prefix ST_. Active only when StateTree plugin is enabled. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UCKConventionRule_AssetNaming_StateTree : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UCKConventionRule_AssetNaming_StateTree();
};

