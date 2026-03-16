// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperConvention.generated.h"

/** How to apply a RuleOverride: keep base rule, disable it, or replace with another rule instance. */
UENUM(BlueprintType)
enum class EConventionRuleOverrideMode : uint8
{
	UseBase,
	Off,
	Replace
};

/**
 * Describes how to override a single rule inherited from the extended convention.
 * RuleId must match a rule from the base (e.g. folder-structure-character). UseBase = keep as is, Off = skip, Replace = use ReplacementRule.
 */
USTRUCT(BlueprintType)
struct CONVENTIONKEEPEREDITOR_API FRuleOverride
{
	GENERATED_BODY()

	/** Id of the rule from the extended convention to override. Dropdown is filled from GetAvailableRuleIds() (effective rules of the base). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetOptions = "GetAvailableRuleIds"))
	FName RuleId;

	/** UseBase = keep the base rule; Off = disable this rule; Replace = use ReplacementRule instead (e.g. custom folder-structure-character). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConventionRuleOverrideMode Mode = EConventionRuleOverrideMode::UseBase;

	/** When Mode == Replace, this rule is used instead of the base rule with the same RuleId. Must be the same rule type (e.g. FolderStructure). */
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

	/** Display name of this convention (e.g. "UHL", "My Project"). Shown in UI and in Settings when choosing a convention. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	/** Short description of this convention. Shown in UI and documentation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText Description;

	/** URL to convention documentation (e.g. style guide or project wiki). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DocsLink;

	/**
	 * Base convention to extend (ESLint-style). Effective rules = base's GetEffectiveRules() with RuleOverrides applied, then this Convention's Rules.
	 * When Extends Convention (Asset) is set, this field is ignored and the asset is used as the base.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention (Class)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention", EditCondition = "!bExtendsConventionAssetIsSet"))
	TSubclassOf<UConventionKeeperConvention> ExtendsConvention;

	/**
	 * Optional: extend a specific Convention asset (e.g. created via Asset Actions). When set, this asset is the base instead of Extends Convention class CDO.
	 * Use when you need to extend a customized instance (e.g. forked UHL with different Rules) rather than the class default.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention (Asset)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention"))
	TSoftObjectPtr<UConventionKeeperConvention> ExtendsConventionAsset;

	/** Internal: true when ExtendsConventionAsset is set; used to hide "Extends Convention (Class)" in the editor. */
	UPROPERTY(Transient, meta = (EditCondition = "false", EditConditionHides, NoResetToDefault))
	bool bExtendsConventionAssetIsSet = false;

	/**
	 * Per-rule overrides for rules inherited from the base. Each entry: RuleId (from base), Mode (UseBase / Off / Replace), optional ReplacementRule.
	 * Example: RuleId=folder-structure-character, Mode=Off — that rule is not run; Mode=Replace + ReplacementRule = your custom rule instance.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRuleOverride> RuleOverrides = {};

	/**
	 * Read-only. Rules inherited from the extended convention (before overrides). Populated when ExtendsConvention or ExtendsConventionAsset is set.
	 * Shown so you can see which rules come from the base; edit overrides via RuleOverrides, not here.
	 */
	UPROPERTY(Transient, VisibleDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false"))
	TArray<TObjectPtr<UConventionKeeperRule>> ExtendedRules = {};

	/**
	 * This convention's own rules. When not extending: these are the only rules (root convention). When extending: these are added after the base rules (with overrides applied).
	 * Example: UHL has Rules = [folder-structure-content, folder-structure-project-name, ...]; your Convention extends UHL and adds one more rule in Rules.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rules"))
	TArray<TObjectPtr<UConventionKeeperRule>> Rules = {};

	/**
	 * Returns the final list of rules used for validation: base rules (if extending) with RuleOverrides applied (Off/Replace), then this Convention's Rules.
	 * Call this when running validation; do not iterate Rules directly if the convention extends another.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UConventionKeeperRule*> GetEffectiveRules() const;

	/**
	 * Returns a localized short description for the given RuleId. Override in subclasses (e.g. UHLConvention) to supply per-rule, per-language text.
	 * Used by rules for GetDisplayDescription(); if empty, rule falls back to DescriptionKey or Description.
	 */
	virtual FText GetLocalizedRuleDescription(FName RuleId) const;

	/** Runs folder structure validation for all rules that apply to the full Content tree (no path filter). */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ValidateFolderStructures();
	void ValidateFolderStructures_Implementation();

	/** Runs folder structure validation only for paths under SelectedPaths (Content/ form). Used when user selects folders in the Content Browser and runs validation. */
	UFUNCTION(BlueprintCallable)
	void ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths);

	/** Returns true if the directory exists; placeholders in DirectoryPath are resolved using the given map. */
	bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);

	/** Returns the actual base convention: ExtendsConventionAsset if set, otherwise the CDO of ExtendsConvention. */
	UConventionKeeperConvention const* GetResolvedExtendsConvention() const;

	/** Returns RuleIds of the extended convention's effective rules. Used by the RuleOverride.RuleId dropdown so you pick a valid id. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Convention Keeper")
	TArray<FString> GetAvailableRuleIds() const;

	//~UObject interface
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~End of UObject interface

private:
	void SyncExtendsConventionAssetFlag();
	void RefreshExtendedRules();
};

