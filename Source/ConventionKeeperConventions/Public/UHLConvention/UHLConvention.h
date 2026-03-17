// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention/ConventionKeeperConvention.h"
#include "UHLConvention.generated.h"

/** Alias for Convention Keeper convention with display name "UHL Convention". Same rules as UConventionKeeperConvention. */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, AutoExpandCategories = ("Default"))
class CONVENTIONKEEPERCONVENTIONS_API UUHLConvention : public UConventionKeeperConvention
{
	GENERATED_BODY()

public:
	UUHLConvention();
};
