// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "CKConventionRule_AssetNaming_AnimSequence.generated.h"

/** CKConvention override: Animation Sequence uses prefix AS_ (not A_ as in UE5 Style Guide). */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UCKConventionRule_AssetNaming_AnimSequence : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UCKConventionRule_AssetNaming_AnimSequence();
};
