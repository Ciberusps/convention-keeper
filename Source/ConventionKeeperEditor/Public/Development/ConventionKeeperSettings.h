// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention.h"
#include "ConventionKeeperSettings.generated.h"


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

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FString> ExceptionFolders = {
		"MyCustomFOlder2323",
		"RetardedFolderForMyDrawings1337",
	};

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
