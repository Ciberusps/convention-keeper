// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/TokenizedMessage.h"
#include "UObject/Object.h"
#include "ConventionKeeperRule.generated.h"

class UConventionKeeperConvention_Base;

/** Severity when a rule fails: Error (red in Message Log) or Warning (yellow). */
UENUM(BlueprintType)
enum class EConventionRuleSeverity : uint8
{
	Error,
	Warning
};

inline EMessageSeverity::Type ConventionKeeperRuleSeverityToMessageSeverity(EConventionRuleSeverity RuleSeverity)
{
	return RuleSeverity == EConventionRuleSeverity::Warning ? EMessageSeverity::Warning : EMessageSeverity::Error;
}

UCLASS(Abstract, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Stable identifier for this rule. Used for:
	 * - RuleOverrides in Convention (disable/replace by id),
	 * - Documentation URL (Docs/Rules/{RuleId}.md),
	 * - Clickable [RuleId] link in validation messages.
	 * Use kebab-case, e.g. folder-structure-content, naming-convention-pascalcase.
	 * Empty = rule is not overridable and has no doc link.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName RuleId;

	/**
	 * Short description of what this rule checks. Shown in the Convention details and in docs.
	 * When DescriptionKey is set, Convention can override this via GetLocalizedRuleDescription (e.g. per-language).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	/**
	 * If set, the displayed description is taken from Convention's localization (GetLocalizedRuleDescription(RuleId))
	 * or from the global ConventionKeeper loc table (key = DescriptionKey). Use when the Convention provides
	 * localized strings; otherwise leave empty and use Description.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false", EditConditionHides))
	FName DescriptionKey;

	/**
	 * Severity when validation fails: Error (red in Message Log) or Warning (yellow).
	 * Does not change what is checked, only how failures are reported.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EConventionRuleSeverity Severity = EConventionRuleSeverity::Error;

	/** Returns localized description. Prefers Convention->GetLocalizedRuleDescription when Convention is set; else DescriptionKey (global loc) or Description. */
	FText GetDisplayDescription(const UConventionKeeperConvention_Base* Convention = nullptr) const;

	/**
	 * Override the path to the rule's markdown doc. If empty, path is built from Settings:
	 * DocsRulePathTemplate with {RuleId} replaced (e.g. Docs/Rules/folder-structure-content.md).
	 * Use when the doc lives elsewhere, e.g. "Docs/MyRules/custom-rule.md".
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Doc path override"))
	FString DocPathOverride;

	/**
	 * Read-only. Full URL to the rule documentation (GitHub blob). Built from Settings DocsRepositoryUrl,
	 * DocsBranch and doc path. Shown in details; copy and open in browser.
	 */
	UPROPERTY(Transient, VisibleAnywhere, meta = (DisplayName = "Documentation URL", ReadOnly))
	FString DocumentationUrl;

	/**
	 * Read-only. Markdown content loaded from the local doc file (project or plugin Docs path).
	 * Used to show the rule text in-editor. If the file is missing, shows "View at link only."
	 */
	UPROPERTY(Transient, VisibleAnywhere, meta = (DisplayName = "Documentation (markdown)", ReadOnly, MultiLine = true))
	FString DocumentationContent;

	/** Full URL to the rule documentation (GitHub blob). Empty if DocsRepositoryUrl not set. */
	FString GetDocumentationUrl() const;

	/** URL for message log link: localized path if that file exists, otherwise English path. English doc must always exist. */
	FString GetDocumentationUrlForDisplay() const;

	/** Raw URL to fetch markdown content (e.g. raw.githubusercontent.com). Empty if no doc URL. */
	FString GetDocumentationRawUrl() const;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanValidate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;
	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Validate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);

	/**
	 * Converts a path to a normalized form: forward slashes, trailing slash.
	 * Used by FolderStructure and AssetNaming for comparison and scope. Example: "Content/Game/Abilities" → "Content/Game/Abilities/".
	 */
	static FString NormalizeRelativePath(const FString& InPath);

#if WITH_EDITOR
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void RefreshDocumentationFields();
	/** Logs to ConventionKeeper: [RuleId] as clickable doc link (localized if exists, else en), then MessageBody, optional path/suffix. Rule null = no link. */
	static void LogRuleMessage(const UConventionKeeperRule* Rule, EMessageSeverity::Type Severity, const FText& MessageBody, const FString* PathForLink = nullptr, const FText& Suffix = FText());
#endif
};
