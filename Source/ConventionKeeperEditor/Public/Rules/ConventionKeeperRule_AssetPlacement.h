// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "Internationalization/Text.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperRule_AssetPlacement.generated.h"

/**
 * Rule: assets of given class(es) must be located under a path that contains a required segment (e.g. Sound Class in SoundClasses).
 * Reuses the same scope and asset iteration as AssetNaming (FolderPathPattern, placeholders, exclusions, GetScopesForValidation).
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule_AssetPlacement : public UConventionKeeperRule
{
	GENERATED_BODY()

public:
	/**
	 * Folder path pattern with placeholders (e.g. Content/{ProjectName}). Only assets under matching paths are validated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RelativePath))
	FDirectoryPath FolderPathPattern;

	/** If non-empty, only assets of these classes are checked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "/Script/CoreUObject.Object"))
	TArray<TSubclassOf<UObject>> AssetClasses;

	/** Class paths resolved at runtime (e.g. /Script/Engine.SoundClass). Use when the class is in an optional module. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Asset Class Paths (optional modules)"))
	TArray<FString> AssetClassPaths;

	/**
	 * Required path segment: the asset's path must contain this segment (e.g. "SoundClasses" → path must contain "/SoundClasses/").
	 * Used as a path segment, so "SoundClasses" matches Content/Game/Audio/SoundClasses/MyAsset but not Content/Game/SoundClassesFolder/Other.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Required Path Segment"))
	FString RequiredPathSegment;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/** Override to skip specific assets. Default: true. */
	virtual bool ShouldValidateAsset(const FAssetData& AssetData) const { return true; }

	/** True if path (Content/... with forward slashes) contains RequiredPathSegment as a path segment. */
	static bool PathContainsSegment(const FString& NormalizedPath, const FString& Segment);
};
