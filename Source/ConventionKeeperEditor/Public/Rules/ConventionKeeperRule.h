// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConventionKeeperRule.generated.h"

UENUM(BlueprintType)
enum class EConventionRuleSeverity : uint8
{
	Error,
	Warning
};

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

	/** Severity when this rule fails (Error or Warning). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EConventionRuleSeverity Severity = EConventionRuleSeverity::Error;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanValidate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;
	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Validate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);

	/** Normalized project-relative path: forward slashes, trailing slash. Shared by FolderStructure and AssetNaming. */
	static FString NormalizeRelativePath(const FString& InPath);
};
