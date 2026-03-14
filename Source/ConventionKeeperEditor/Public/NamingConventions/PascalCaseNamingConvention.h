// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperNamingConvention.h"
#include "PascalCaseNamingConvention.generated.h"


UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, AutoExpandCategories = ("Default"))
class CONVENTIONKEEPEREDITOR_API UPascalCaseNamingConvention : public UConventionKeeperNamingConvention
{
	GENERATED_BODY()

public:
	UPascalCaseNamingConvention();
};