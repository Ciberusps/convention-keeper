// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperNamingConvention.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperConvention.generated.h"

UENUM(BlueprintType)
enum class EConventionRuleOverrideMode : uint8
{
	UseBase,
	Off,
	Replace
};

USTRUCT(BlueprintType)
struct CONVENTIONKEEPEREDITOR_API FRuleOverride
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RuleId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConventionRuleOverrideMode Mode = EConventionRuleOverrideMode::UseBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Mode == EConventionRuleOverrideMode::Replace"))
	TObjectPtr<UConventionKeeperRule> ReplacementRule = nullptr;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperConvention : public UObject
{
	GENERATED_BODY()

public:
	// should introspect all templates recursively
	// e.g. we can have `/{ProjectName}/{CharacterName}/{SomethingName}`
	// {ProjectName} - placeholder, {CharacterName} and {SomethingName} are templates
	/**
	 * Scans a single path string for segments of the form "{Name}",
	 * ignores any in GlobalPlaceholders, and returns the rest.
	 */
	UFUNCTION()
	static TSet<FString> ExtractTemplatesFromPath(
		const FString& Path,
		const TMap<FString, FString>& GlobalPlaceholders
	);

	/**
	 * Given a “templated” path (absolute or relative) with placeholders like
	 * "{SomeTemplate}", this will:
	 *  1) split off the leading literal segments (e.g. "/RootFolder"),
	 *  2) for each placeholder segment, recurse into each matching subdirectory
	 *     of the current set of paths,
	 *  3) accumulate *all* matched folder‐paths at each placeholder level,
	 *  4) return that list.
	 *
	 * Example:
	 *   Pattern = "/RootFolder/{A}/{B}"
	 *   Disk contains:
	 *     /RootFolder/Foo
	 *     /RootFolder/Bar
	 *     /RootFolder/Foo/X
	 *     /RootFolder/Foo/Y
	 *
	 *   ResolveTemplatePaths(Pattern) ->
	 *     [ "/RootFolder/Foo",
	 *       "/RootFolder/Bar",
	 *       "/RootFolder/Foo/X",
	 *       "/RootFolder/Foo/Y" ]
	 */
	UFUNCTION()
	static TArray<FString> ResolveTemplatePaths(
		const FString& FullPattern,
		const TMap<FString, FString>& GlobalPlaceholders
	);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UConventionKeeperNamingConvention> NamingConvention;

	/** Convention to extend (ESLint-style extends). If set, effective rules = extended GetEffectiveRules() + RuleOverrides + AdditionalRules. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention"))
	TSubclassOf<UConventionKeeperConvention> ExtendsConvention;

	/** Override or disable rules from base by RuleId. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRuleOverride> RuleOverrides = {};

	/** Root rules (used when ExtendsConvention is null). Read-only: extend via ExtendsConvention and override via RuleOverrides / AdditionalRules. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false"))
	TArray<TObjectPtr<UConventionKeeperRule>> Rules = {};

	/** Extra rules when extending a base; merged after base rules and overrides. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Additional Rules"))
	TArray<TObjectPtr<UConventionKeeperRule>> AdditionalRules = {};

	/** Effective rules: from base (if any) with RuleOverrides applied, then AdditionalRules. Use this for validation. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UConventionKeeperRule*> GetEffectiveRules() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ValidateFolderStructures();
	void ValidateFolderStructures_Implementation();

	UFUNCTION(BlueprintCallable)
	void ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths);

	bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);

};
