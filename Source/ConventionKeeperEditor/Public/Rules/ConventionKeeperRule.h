// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConventionKeeperRule.generated.h"

UCLASS(Abstract, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule : public UObject
{
	GENERATED_BODY()

public:
	/** Stable id for extend/override (e.g. folder-content); empty = no override key. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName RuleId;

	/** What this rule checks; shown in editor and docs. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanValidate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;
	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Validate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);
};
