// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention_Base.h"
#include "ConventionKeeperSettings.generated.h"

/** Project default language for rule descriptions and message log. */
UENUM(BlueprintType)
enum class EConventionKeeperLanguage : uint8
{
	Auto    UMETA(DisplayName = "Auto (system)"),
	English UMETA(DisplayName = "English"),
	Russian UMETA(DisplayName = "Russian")
};

/** Per-user language override (Saved/Config). Overrides project Default Language when not UseProjectDefault. */
UENUM(BlueprintType)
enum class EConventionKeeperLanguageOverride : uint8
{
	UseProjectDefault UMETA(DisplayName = "Use project default"),
	English           UMETA(DisplayName = "English"),
	Russian           UMETA(DisplayName = "Russian")
};

/** Per-user validation override (Saved/Config). Overrides project Enable validation when not UseProjectDefault. */
UENUM(BlueprintType)
enum class EConventionKeeperValidationOverride : uint8
{
	UseProjectDefault UMETA(DisplayName = "Use project default"),
	Enabled           UMETA(DisplayName = "Enabled"),
	Disabled          UMETA(DisplayName = "Disabled")
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
 * Project settings for Convention Keeper. Stored in Config/DefaultEditor.ini (project).
 * Defines which convention is used, exclusions, documentation URLs, and placeholders for rule paths.
 */
UCLASS(Config="Editor", DefaultConfig, meta = (DisplayName="ConventionKeeper"))
class CONVENTIONKEEPEREDITOR_API UConventionKeeperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UConventionKeeperSettings();

	/**
	 * Value for the {ProjectName} placeholder in rule paths (e.g. Content/{ProjectName}/...).
	 * Defaults to the current project name (FApp::GetProjectName()). Change if your Content root uses another folder name.
	 */
	UPROPERTY(Config, EditAnywhere)
	FString ProjectNameFolder = FApp::GetProjectName();

	/**
	 * Convention class used for validation when Convention Asset is not set. The class's default object (CDO) is used.
	 * When Convention Asset is set, this field is ignored and the asset is used instead (so you can have a class in source and override with an instance in content).
	 */
	UPROPERTY(Config, EditAnywhere, meta = (AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention_Base", EditCondition = "!bConventionAssetIsSet"))
	TSubclassOf<UConventionKeeperConvention_Base> Convention;

	/**
	 * Optional: a Convention asset (e.g. created via Asset Actions). When set, this asset is used for all validation instead of Convention class CDO.
	 * Use when you need to edit the convention in the editor (Rules, RuleOverrides) without changing code.
	 */
	UPROPERTY(Config, EditAnywhere, meta = (AllowedClasses = "/Script/ConventionKeeperEditor.ConventionKeeperConvention_Base"))
	TSoftObjectPtr<UConventionKeeperConvention_Base> ConventionAsset;

	/** Internal: true when ConventionAsset is set; used to hide Convention (class) in the editor. */
	UPROPERTY(Transient, meta = (EditCondition = "false", EditConditionHides, NoResetToDefault))
	bool bConventionAssetIsSet = false;

	/** Returns the convention used for validation: ConventionAsset if set, otherwise the CDO of Convention. */
	UConventionKeeperConvention_Base* GetResolvedConvention() const;

	/**
	 * Project default: master switch for all validations. When false, no rules run (menu, context menu, on save, commandlet).
	 * Can be overridden per user in Convention Keeper (Local) → Local Override Validation (Saved/Config).
	 * Running validation while off shows one message in the Message Log (or commandlet log), e.g. "ConventionKeeper is offline. Enable in Project Settings → Convention Keeper."
	 * Message text is in Localization (ValidationDisabled); alternative punchlines you can use there:
	 * - "ConventionKeeper AFK. Wake it up in Project Settings → Convention Keeper."
	 * - "ConventionKeeper went for coffee. Enable in settings when you're back."
	 * - "ConventionKeeper is taking a nap. Enable validation in Project Settings → Convention Keeper."
	 */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Enable validation"))
	bool bValidationEnabled = true;

	/** Returns whether validation runs: respects Local Override (Convention Keeper (Local)) first, then this project setting. */
	bool GetEffectiveValidationEnabled() const;

	/**
	 * When true, after saving an asset the convention is validated (including Asset Naming rules for that path).
	 * Disabled automatically during autosave. Turn off if you want validation only from the menu/commandlet.
	 */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Validate on save"))
	bool bValidateAssetNamingOnSave = true;

	/**
	 * Paths that are skipped by all rules. Entries can be folders (with trailing slash) or assets (no trailing slash), in Content/ form.
	 * Example: "Content/Developers/", "Content/Game/TestMap" — those paths are not validated. Placeholders like {ProjectName} are resolved using GetPlaceholders().
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FString> Exclusions = {};

	/**
	 * When true, every rule check is logged: failures as Error/Warning, passed checks as Info. Useful to see which paths were validated.
	 */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay)
	bool bDebug = false;

	/**
	 * Default language for rule descriptions and message log. Auto = use editor/system language; English/Russian = force that language.
	 * Can be overridden per user via Convention Keeper (Local) → Local Override Language.
	 */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Default Language"))
	EConventionKeeperLanguage DefaultLanguage = EConventionKeeperLanguage::Auto;

	/** Returns the effective language code ("en" or "ru") for localization: respects Local Override, then Default Language, then system. */
	FString GetEffectiveLanguageCode() const;

	/**
	 * Base URL of the repository where rule docs live. Used to build clickable links in the Message Log: {Url}/blob/{Branch}/{DocPathTemplate with RuleId}.
	 * Default points to the upstream plugin repo; set to your fork if you host docs there.
	 */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Documentation repository URL"))
	FString DocsRepositoryUrl = TEXT("https://github.com/Ciberusps/convention-keeper");

	/** Git branch or tag used in doc links (e.g. main, master). Must match the branch where your Docs/Rules/*.md files exist. */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Documentation branch"))
	FString DocsBranch = TEXT("main");

	/**
	 * Path template for rule documentation, relative to the repo root. {RuleId} is replaced by the rule's RuleId (e.g. folder-structure-content).
	 * Example: "Docs/Rules/{RuleId}.md" → Docs/Rules/folder-structure-content.md. Localized docs are looked up under Docs/Rules/{Lang}/{RuleId}.md (e.g. ru).
	 */
	UPROPERTY(Config, EditAnywhere, AdvancedDisplay, meta = (DisplayName = "Rule doc path template"))
	FString DocsRulePathTemplate = TEXT("Docs/Rules/{RuleId}.md");

	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override { return FApp::GetProjectName(); }
	//~End of UDeveloperSettings interface

	//~UObject interface
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~End of UObject interface

	/** Returns placeholders for rule paths: {ProjectName} = ProjectNameFolder, plus any entries from Placeholders. Keys use braces, e.g. "{ProjectName}". */
	TMap<FString, FString> GetPlaceholders() const;

protected:
	/**
	 * Extra placeholders for path templates. Merged with {ProjectName} in GetPlaceholders().
	 * Example: "CharacterName" -> "Zombie" (use keys with or without braces; they are normalized when resolving paths).
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> Placeholders = {};

};

/**
 * Per-user Convention Keeper settings. Stored in Saved/Config/ConventionKeeperUserSettings.ini (not in project),
 * so each developer can choose language and validation override without affecting other users or project config.
 */
UCLASS(Config = "ConventionKeeperUserSettings", meta = (DisplayName = "Convention Keeper (Local)"))
class CONVENTIONKEEPEREDITOR_API UConventionKeeperLocalSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * Override the language for rule descriptions and message log for this machine. Use project default to follow the project's Default Language (Settings).
	 * English/Russian = force that language regardless of project or system.
	 */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Local Override Language"))
	EConventionKeeperLanguageOverride LocalOverrideLanguage = EConventionKeeperLanguageOverride::UseProjectDefault;

	/**
	 * Override whether validation runs for this user. Use project default to follow project Enable validation.
	 * Enabled/Disabled = force on or off for this machine (Saved/Config, not in project).
	 */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Local Override Validation"))
	EConventionKeeperValidationOverride LocalOverrideValidation = EConventionKeeperValidationOverride::UseProjectDefault;

	virtual FName GetCategoryName() const override { return FApp::GetProjectName(); }

	/** Path to the user-only config file in Saved/Config (never in project). */
	static FString GetUserSettingsConfigPath();

	//~UObject interface
	virtual void PostLoad() override;
	/** Saves to Saved/Config/ConventionKeeperUserSettings.ini (hides UObject::SaveConfig, not virtual in base). */
	void SaveConfig(uint64 RequiredPropertyFlags = CPF_Config, const TCHAR* Filename = nullptr, FConfigCacheIni* Config = nullptr, bool bAllowCopyToDefaultObject = true);
};
