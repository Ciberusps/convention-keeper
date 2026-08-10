// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetValidation.h"
#include "ConventionKeeperRule_StateTreeDeprecatedNodes.generated.h"

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, meta = (DisplayName = "StateTree Deprecated Nodes"))
class CONVENTIONKEEPERVALIDATIONEDITOR_API UConventionKeeperRule_StateTreeDeprecatedNodes : public UConventionKeeperRule_AssetValidation
{
	GENERATED_BODY()

public:
	UConventionKeeperRule_StateTreeDeprecatedNodes(const FObjectInitializer& ObjectInitializer);
};
