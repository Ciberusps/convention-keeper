// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ConventionKeeperConvention.h"
#include "ConventionAssetFactory.generated.h"

UCLASS()
class CONVENTIONKEEPEREDITOR_API UConventionFactory : public UFactory
{
	GENERATED_BODY()

public:
	UConventionFactory();

	/** Class chosen in ConfigureProperties; assigned to the new Convention's ExtendsConvention (ESLint-style extends). */
	UPROPERTY(EditAnywhere, Category = Convention)
	TSubclassOf<UConventionKeeperConvention> ExtendsConventionClass;

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(
		UClass* Class,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
};
