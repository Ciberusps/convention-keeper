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

/**
 * Convention: set of rules for validation (folder structure, naming, etc.).
 * Extend only via ExtendsConvention (ESLint-style), not by subclassing.
 * Chained extends are supported: MyConvention extends GodreaperConvention extends UHLConvention.
 */
UCLASS(Blueprintable, BlueprintType)
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

	/** Class to extend when Extends Convention Asset is not set. Disabled when Extends Convention Asset is set. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention (Class)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention", EditCondition = "!bExtendsConventionAssetIsSet"))
	TSubclassOf<UConventionKeeperConvention> ExtendsConvention;

	/** Optional: extend this Convention asset (e.g. created via Asset Actions). When set, used instead of Extends Convention class CDO. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention (Asset)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention"))
	TSoftObjectPtr<UConventionKeeperConvention> ExtendsConventionAsset;

	/** Used by EditCondition only; true when ExtendsConventionAsset is set. */
	UPROPERTY(Transient, meta = (EditCondition = "false", EditConditionHides, NoResetToDefault))
	bool bExtendsConventionAssetIsSet = false;

	/** Override or disable rules from base by RuleId. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRuleOverride> RuleOverrides = {};

	/** Inherited rules from the base convention chain (read-only). Shown when extending; empty when not. */
	UPROPERTY(Transient, VisibleDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false"))
	TArray<TObjectPtr<UConventionKeeperRule>> ExtendedRules = {};

	/** Own rules: root rules when not extending, or rules added after the base when extending. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rules"))
	TArray<TObjectPtr<UConventionKeeperRule>> Rules = {};

	/** Effective rules: from base (if any) with RuleOverrides applied, then Rules. Use this for validation. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UConventionKeeperRule*> GetEffectiveRules() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ValidateFolderStructures();
	void ValidateFolderStructures_Implementation();

	UFUNCTION(BlueprintCallable)
	void ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths);

	bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);

	/** Returns the base convention: ExtendsConventionAsset if set, else ExtendsConvention class CDO. */
	UConventionKeeperConvention const* GetResolvedExtendsConvention() const;

	//~UObject interface
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~End of UObject interface

private:
	void SyncExtendsConventionAssetFlag();
	void RefreshExtendedRules();
};

