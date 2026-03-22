// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperConvention_Base.generated.h"

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

class UConventionKeeperCommandlet;

/**
 * Abstract base for conventions: set of rules for validation (folder structure, naming, etc.).
 * Do not instantiate directly — use subclasses (e.g. UEarendilConvention, UUE5StyleGuideConvention).
 * Extend only via ExtendsConvention (ESLint-style), not by subclassing.
 * Chained extends are supported: e.g. MyConvention extends ParentConvention extends UEarendilConvention.
 */
UCLASS(Blueprintable, BlueprintType)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperConvention_Base : public UObject
{
	GENERATED_BODY()

	friend class UConventionKeeperCommandlet;

public:
	/**
	 * Scans a single path string for segments of the form "{Name}",
	 * ignores any in GlobalPlaceholders, and returns the rest.
	 */
	UFUNCTION()
	static TSet<FString> ExtractTemplatesFromPath(
		const FString& Path,
		const TMap<FString, FString>& GlobalPlaceholders
	);

	/** Display name of this convention (e.g. "Earendil", "My Project"). Shown in UI and in Settings when choosing a convention. */
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention (Class)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention_Base", EditCondition = "!bExtendsConventionAssetIsSet"))
	TSubclassOf<UConventionKeeperConvention_Base> ExtendsConvention;

	/**
	 * Optional: extend a specific Convention asset (e.g. created via Asset Actions). When set, this asset is the base instead of Extends Convention class CDO.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Extends Convention (Asset)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention_Base"))
	TSoftObjectPtr<UConventionKeeperConvention_Base> ExtendsConventionAsset;

	/** Internal: true when ExtendsConventionAsset is set; used to hide "Extends Convention (Class)" in the editor. */
	UPROPERTY(Transient, meta = (EditCondition = "false", EditConditionHides, NoResetToDefault))
	bool bExtendsConventionAssetIsSet = false;

	/**
	 * Per-rule overrides for rules inherited from the base.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRuleOverride> RuleOverrides = {};

	/**
	 * Read-only. Rules inherited from the extended convention (before overrides).
	 */
	UPROPERTY(Transient, VisibleDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false"))
	TArray<TObjectPtr<UConventionKeeperRule>> ExtendedRules = {};

	/**
	 * This convention's own rules. When not extending: these are the only rules. When extending: these are added after the base rules (with overrides applied).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rules"))
	TArray<TObjectPtr<UConventionKeeperRule>> Rules = {};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UConventionKeeperRule*> GetEffectiveRules() const;

	virtual FText GetLocalizedRuleDescription(FName RuleId) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ValidateFolderStructures();
	void ValidateFolderStructures_Implementation();

	UFUNCTION(BlueprintCallable)
	void ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths);

	bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);

	UConventionKeeperConvention_Base const* GetResolvedExtendsConvention() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Convention Keeper")
	TArray<FString> GetAvailableRuleIds() const;

	/** Sets ExtendsConvention and refreshes transient inherited rules immediately. */
	UFUNCTION(BlueprintCallable, Category = "Convention Keeper")
	void SetExtendsConventionClass(TSubclassOf<UConventionKeeperConvention_Base> InExtendsConvention);

	/** Rebuilds transient ExtendedRules from the currently resolved base convention. */
	UFUNCTION(BlueprintCallable, Category = "Convention Keeper")
	void RebuildExtendedRules();

	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	void ValidateFolderStructuresForPathsInternal(
		const TArray<FString>& SelectedPaths,
		const struct FConventionKeeperValidationHooks* Hooks);
	void SyncExtendsConventionAssetFlag();
	void RefreshExtendedRules();
};
