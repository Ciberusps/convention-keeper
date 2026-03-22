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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Mode == EConventionRuleOverrideMode::Replace", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperRule"))
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

	/**
	 * Convention name (UI, pickers). Also the default documentation file id: slugified for Docs/Conventions/{slug}.md unless OverrideDocumentationId is set.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Convention")
	FString Name = "";

	/** Short summary. Full text and references live in the repo markdown for this convention. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Convention", meta = (MultiLine = "true"))
	FText Description;

	/**
	 * If set, used as {ConventionDocId} in the convention doc path template instead of a slug derived from Name.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docs", AdvancedDisplay)
	FName DocsIdOverride;

	/**
	 * Override path to the convention markdown relative to the repo root. If empty, path is built from Settings DocsConventionPathTemplate and documentation id (Name slug or OverrideDocumentationId).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docs", AdvancedDisplay, meta = (DisplayName = "Doc path override"))
	FString DocsPathOverride;

	/** Read-only. Git blob URL for this convention's markdown (from DocsRepositoryUrl / DocsBranch / path template). */
	UPROPERTY(Transient, VisibleAnywhere, Category = "Docs", meta = (DisplayName = "Documentation URL", ReadOnly))
	FString DocsUrl;

	/** Documentation id for URL template: OverrideDocumentationId if set, else slugified Name. */
	FString GetConventionDocumentationSlugForUrls() const;

	/** Full URL to this convention's markdown in the documentation repository. */
	FString GetConventionDocumentationUrl() const;

	/** URL for UI: localized convention doc path if that file exists on disk, else default path (same rules as rule docs). */
	FString GetConventionDocumentationUrlForDisplay() const;

	/**
	 * Base convention to extend (ESLint-style). Effective rules = base's GetEffectiveRules() with RuleOverrides applied, then this Convention's Rules.
	 * When Extends Convention (Asset) is set, this field is ignored and the asset is used as the base.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Convention", meta = (DisplayName = "Extends Convention (Class)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention_Base", EditCondition = "!bExtendsConventionAssetIsSet"))
	TSubclassOf<UConventionKeeperConvention_Base> ExtendsConvention;

	/**
	 * Optional: extend a specific Convention asset (e.g. created via Asset Actions). When set, this asset is the base instead of Extends Convention class CDO.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Convention", meta = (DisplayName = "Extends Convention (Asset)", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention_Base"))
	TSoftObjectPtr<UConventionKeeperConvention_Base> ExtendsConventionAsset;

	/** Internal: true when ExtendsConventionAsset is set; used to hide "Extends Convention (Class)" in the editor. */
	UPROPERTY(Transient, meta = (EditCondition = "false", EditConditionHides, NoResetToDefault))
	bool bExtendsConventionAssetIsSet = false;

    /**
     * This convention's own rules. When not extending: these are the only rules. When extending: these are added after the base rules (with overrides applied).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rules", meta = (DisplayName = "Rules", AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperRule"))
    TArray<TObjectPtr<UConventionKeeperRule>> Rules = {};

	/**
	 * Read-only. Rules inherited from the extended convention (before overrides).
	 */
	UPROPERTY(Transient, VisibleDefaultsOnly, BlueprintReadOnly, Category="Rules", meta = (EditCondition = "false"))
	TArray<TObjectPtr<UConventionKeeperRule>> ExtendedRules = {};

    /**
     * Per-rule overrides for rules inherited from the base.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rules")
    TArray<FRuleOverride> RuleOverrides = {};

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
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif

	/** Refreshes ConventionDocumentationUrl (editor). */
	void RefreshConventionDocumentationFields();

private:
	void ValidateFolderStructuresForPathsInternal(
		const TArray<FString>& SelectedPaths,
		const struct FConventionKeeperValidationHooks* Hooks);
	void SyncExtendsConventionAssetFlag();
	void RefreshExtendedRules();
#if WITH_EDITOR
	/** When extending another convention: if Name / Description are empty, set defaults from the base. */
	void ApplyInheritedConventionDefaultsIfNeeded();
#endif
};
