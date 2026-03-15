// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention.h"
#include "ConventionKeeperSettings.generated.h"

UENUM(BlueprintType)
enum class EConventionKeeperLanguage : uint8
{
	Auto    UMETA(DisplayName = "Auto (system)"),
	English UMETA(DisplayName = "English"),
	Russian UMETA(DisplayName = "Russian")
};

UENUM(BlueprintType)
enum class EConventionKeeperLanguageOverride : uint8
{
	UseProjectDefault UMETA(DisplayName = "Use project default"),
	English           UMETA(DisplayName = "English"),
	Russian           UMETA(DisplayName = "Russian")
};

// USTRUCT(BlueprintType)
// struct UHLCONVENTIONKEEPEREDITOR_API FUHECustomClassIconDescription
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomClassIconDescription")
//     TSoftObjectPtr<UTexture2D> Texture2D;
// 	// deprecated, TODO: remove
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomClassIconDescription", meta=(DeprecatedProperty, DeprecationMessage="Deprecated use Classes"))
//     TSubclassOf<UObject> Class;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomClassIconDescription")
// 	TArray<TSubclassOf<UObject>> Classes;
// };

/**
 *
 */
UCLASS(Config="Editor", DefaultConfig, meta = (DisplayName="ConventionKeeper"))
class CONVENTIONKEEPEREDITOR_API UConventionKeeperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
    UConventionKeeperSettings();

	UPROPERTY(Config, EditAnywhere)
	FString ProjectNameFolder = FApp::GetProjectName();

	/** Class to use when Convention Asset is not set (Blueprint or native class; uses CDO). Disabled when Convention Asset is set. */
	UPROPERTY(Config, EditAnywhere, meta = (AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention", EditCondition = "!bConventionAssetIsSet"))
	TSubclassOf<UConventionKeeperConvention> Convention;

	/** Optional: specific Convention asset (e.g. created via Asset Actions). When set, this is used instead of Convention class CDO. */
	UPROPERTY(Config, EditAnywhere, meta = (AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention"))
	TSoftObjectPtr<UConventionKeeperConvention> ConventionAsset;

	/** Used by EditCondition only; true when ConventionAsset is set so Convention is disabled. */
	UPROPERTY(Transient, meta = (EditCondition = "false", EditConditionHides, NoResetToDefault))
	bool bConventionAssetIsSet = false;

	/** Returns the Convention to use: ConventionAsset if set, otherwise Convention class CDO. */
	UConventionKeeperConvention* GetResolvedConvention() const;

	/** Folder paths (trailing slash) and/or asset paths (no trailing slash) in Content/ form. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FString> Exclusions = {};

	/** When enabled, convention (including Asset Naming rules) is validated after saving an asset. Disabled during autosave. */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Validate on save"))
	bool bValidateAssetNamingOnSave = true;

    /** When enabled, every check is logged: failures as Error/Warning, passed checks as Info. */
    UPROPERTY(Config, EditAnywhere, AdvancedDisplay)
    bool bDebug = false;

	/** Default language for the project. Used when no local override is set. Auto = use system/editor language. */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Default Language"))
	EConventionKeeperLanguage DefaultLanguage = EConventionKeeperLanguage::Auto;

	/** Resolved language code for localization: "en" or "ru". Uses local override if set, else project default (Auto → system). */
	FString GetEffectiveLanguageCode() const;

	/** Base URL for rule documentation. Used to build links like {Url}/blob/{Branch}/{DocPathTemplate}. Default: upstream plugin repo. */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Documentation repository URL"))
	FString DocsRepositoryUrl = TEXT("https://github.com/Ciberusps/convention-keeper");

	/** Branch or tag for doc links (e.g. main, master). */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Documentation branch"))
	FString DocsBranch = TEXT("main");

	/** Path template relative to repo; {RuleId} is replaced by the rule id (e.g. docs/rules/{RuleId}.md for repo root). */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Rule doc path template"))
	FString DocsRulePathTemplate = TEXT("Docs/Rules/{RuleId}.md");

	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override { return FApp::GetProjectName(); }
	//~End of UDeveloperSettings interface

	//~UObject interface
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~End of UObject interface

	TMap<FString, FString> GetPlaceholders() const;

protected:
	// for explicitly added placeholders
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> Placeholders = {};

};

/**
 * Per-user language override. Stored in Saved/Config (not in project). When "Use project default", project Default Language is used.
 */
UCLASS(Config = "EditorPerProjectUserSettings", DefaultConfig, meta = (DisplayName = "Convention Keeper (Local)"))
class CONVENTIONKEEPEREDITOR_API UConventionKeeperLocalSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Override language for this user. Use project default to follow project Default Language. */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Local Override Language"))
	EConventionKeeperLanguageOverride LocalOverrideLanguage = EConventionKeeperLanguageOverride::UseProjectDefault;

	virtual FName GetCategoryName() const override { return FApp::GetProjectName(); }
};
