// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConventionKeeperRule.generated.h"

class UConventionKeeperConvention;

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

	/** If set, localized description is used (Settings → Language). Otherwise Description is shown. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false", EditConditionHides))
	FName DescriptionKey;

    /** Severity when this rule fails (Error or Warning). */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EConventionRuleSeverity Severity = EConventionRuleSeverity::Error;

	/** Returns localized description. Prefers Convention->GetLocalizedRuleDescription when Convention is set; else DescriptionKey (global loc) or Description. */
	FText GetDisplayDescription(const UConventionKeeperConvention* Convention = nullptr) const;

	/** Optional override for doc path (e.g. docs/rules/custom-name.md). If empty, path is built from Settings template and RuleId. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Doc path override"))
	FString DocPathOverride;

	/** URL to the rule documentation (GitHub). Read-only. Copy and open in browser; editor has no built-in URL type with open button. */
	UPROPERTY(Transient, VisibleAnywhere, meta = (DisplayName = "Documentation URL", ReadOnly))
	FString DocumentationUrl;

	/** Markdown from local file only (docs path from Settings). If file is missing, shows «View at link only.» */
	UPROPERTY(Transient, VisibleAnywhere, meta = (DisplayName = "Documentation (markdown)", ReadOnly, MultiLine = true))
	FString DocumentationContent;

	/** Full URL to the rule documentation (GitHub blob). Empty if DocsRepositoryUrl not set. */
	FString GetDocumentationUrl() const;

	/** Raw URL to fetch markdown content (e.g. raw.githubusercontent.com). Empty if no doc URL. */
	FString GetDocumentationRawUrl() const;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanValidate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;
	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Validate(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders);

	/** Normalized project-relative path: forward slashes, trailing slash. Shared by FolderStructure and AssetNaming. */
	static FString NormalizeRelativePath(const FString& InPath);

#if WITH_EDITOR
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void RefreshDocumentationFields();
#endif
};
