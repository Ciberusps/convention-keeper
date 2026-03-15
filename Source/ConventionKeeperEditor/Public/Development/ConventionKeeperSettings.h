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

    /** When enabled, every check is logged: failures as Error/Warning, passed checks as Info. */
    UPROPERTY(Config, EditAnywhere)
    bool bDebug = false;

	/** Language for rule descriptions and validation messages. Auto = use system/editor language (ru if Russian, else en). */
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Language"))
	EConventionKeeperLanguage Language = EConventionKeeperLanguage::Auto;

	/** Resolved language code for localization: "en" or "ru". When Auto, derived from system/editor language. */
	FString GetEffectiveLanguageCode() const;

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
