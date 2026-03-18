// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "Internationalization/Text.h"

class IAssetRegistry;
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperRule_AssetNaming.generated.h"

/** One scope to validate: QueryPath is the folder to scan; OnlyAssetPaths, when non-empty, restricts to those assets (e.g. when user selected a single asset). */
USTRUCT(BlueprintType)
struct CONVENTIONKEEPEREDITOR_API FAssetNamingScopeEntry
{
	GENERATED_BODY()
	FString RulePath;
	FString QueryPath;
	TArray<FString> OnlyAssetPaths;
};

/**
 * Rule: assets in a templated folder path must follow a naming pattern.
 * - Folder path can contain placeholders (e.g. Content/{ProjectName}/Characters/{CharacterName}/Animations).
 * - AssetClasses: only these classes are checked.
 * - NamingTemplate: e.g. "AS_{CharacterName}_" — placeholders are filled from the folder path; the rest of the name is free,
 *   but if it ends with _<number>, that number must be zero-padded to NumberPaddingDigits (e.g. AS_Zombie_Jump_01 not _1).
 * - Optional Prefix/Suffix for simpler fixed prefix/suffix checks.
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule_AssetNaming : public UConventionKeeperRule
{
	GENERATED_BODY()

public:
	/**
	 * Folder path pattern with placeholders (e.g. Content/{ProjectName}/Characters/{CharacterName}/Animations).
	 * Only assets in folders matching this path (after resolving placeholders) are validated. Placeholders in the path can be used in NamingTemplate.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RelativePath))
	FDirectoryPath FolderPathPattern;

	/**
	 * If non-empty, only assets of these classes are checked (e.g. AnimSequence, AnimMontage). Empty = all asset classes in the folder.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "/Script/CoreUObject.Object"))
	TArray<TSubclassOf<UObject>> AssetClasses;

	/**
	 * Optional class paths (e.g. "/Script/ControlRigDeveloper.ControlRigBlueprint") resolved at runtime. Use instead of AssetClasses when the class lives in an optional module to avoid hard dependencies.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Asset Class Paths (optional modules)"))
	TArray<FString> AssetClassPaths;

	/**
	 * When non-empty, only Blueprint assets whose parent class path matches one of these are validated (e.g. /Script/Engine.AIController). Used with AssetClassPaths = ["/Script/Engine.Blueprint"].
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Blueprint Parent Class Paths"))
	TArray<FString> BlueprintParentClassPaths;

	/**
	 * Naming template: required prefix for asset names. Placeholders like {CharacterName} are filled from the folder path.
	 * Example: "AS_{CharacterName}_" in folder .../Zombie/Animations → required prefix "AS_Zombie_". Name may have a trailing _NN (zero-padded to NumberPaddingDigits).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NamingTemplate;

	/**
	 * When the asset name ends with _<digits>, that part must be zero-padded to this many digits. Example: 2 → AS_Zombie_Jump_01 allowed, AS_Zombie_Jump_1 fails.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberPaddingDigits = 2;

	/** If non-empty, asset names must start with this exact string. Can be used alone or together with NamingTemplate (both are enforced). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Prefix;

	/** When non-empty, asset names must start with one of these (e.g. CR_, Rig_). Takes precedence over Prefix for the prefix check when set. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> AllowedPrefixes;

	/** If non-empty, asset names must end with this exact string (e.g. "_Physics"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Suffix;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/**
	 * Override to skip assets that do not belong to this rule (e.g. Decal rule only validates assets that are actually decals).
	 * When returns false, the asset is not validated by this rule. Default: true.
	 * For Blueprint rules, Registry and BlueprintByClassName are set: use GetNativeParentClassPath to resolve parent chain via registry (no asset loading).
	 */
	virtual bool ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry = nullptr, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr) const { return true; }

	/**
	 * Override to supply a per-asset required prefix (e.g. M_ vs PP_ for materials by domain).
	 * When returns true, OutPrefix is used for this asset's prefix check instead of Prefix/AllowedPrefixes.
	 * When returns false, the rule uses the normal Prefix or AllowedPrefixes.
	 */
	virtual bool GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const { return false; }

	/**
	 * Override to apply custom suffix validation (e.g. texture suffix must be _D, _N, _ERO from allowed letters).
	 * When returns true, OutValid is used as the suffix check result instead of the default (Suffix.IsEmpty() || AssetName.EndsWith(Suffix)).
	 * When returns false, the default suffix check is used.
	 */
	virtual bool GetCustomSuffixValidity(const FString& AssetName, const FString& UsedPrefix, bool& OutValid) const { return false; }

	/**
	 * When custom suffix validation fails, override to return a specific message. Empty = use default suffix message.
	 */
	virtual FText GetCustomSuffixFailureMessage(const FString& AssetName, const FString& UsedPrefix) const { return FText(); }

	/** Returns the required prefix for an asset name given path placeholder values (e.g. CharacterName=Zombie). */
	static FString ResolveNamingTemplate(const FString& Template, const TMap<FString, FString>& PathPlaceholders);
	/** If Name ends with _<digits>, returns true when that part is zero-padded to PaddingDigits (e.g. _01). */
	static bool IsNumberSuffixValid(const FString& AssetName, int32 PaddingDigits);
	/** Suggested corrected name when only the number suffix is wrong (e.g. AS_Zombie_Jump_1 → AS_Zombie_Jump_01). */
	static FString SuggestZeroPaddedName(const FString& AssetName, int32 PaddingDigits);

	/** Fills OutPathPlaceholders from resolved path using pattern with {Placeholder} segments. GlobalPlaceholders keys must include braces (e.g. "{ProjectName}"). */
	static bool ExtractPathPlaceholders(const FString& PatternPath, const FString& ResolvedPath, const TMap<FString, FString>& GlobalPlaceholders, TMap<FString, FString>& OutPathPlaceholders);

	/** Fills OutParentPath with the Blueprint parent class path (ParentClass or NativeParentClass tag, normalized). Returns false if empty. */
	static bool GetBlueprintParentClassPath(const FAssetData& AssetData, FString& OutParentPath);
	/** True if NormalizedParent equals Path or is a subclass path (e.g. /Script/GameCode.BP_Child). */
	static bool ParentMatches(const FString& NormalizedParent, const TCHAR* Path);
	/** True if NativeRoot matches Path (ParentMatches or Contains); use for NativeRoot from tags that may be "Prefix./Script/Module.ClassName". */
	static bool NativeRootMatchesPath(const FString& NativeRoot, const TCHAR* Path);

	/** Resolves Blueprint parent chain via Asset Registry (no loading). OutNativeRoot = native base class path; returns true if resolved to a known native base. BlueprintByClassName optional to avoid repeated GetAssets. */
	static bool GetNativeParentClassPath(const FAssetData& AssetData, IAssetRegistry& Registry, FString& OutNativeRoot, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr);

	/** Call from specialty Blueprint rules (BPFL, BPI, BPML, Component, etc.) in constructor to register native path(s). Generic BP rule will skip assets whose native root matches any registered path. */
	static void RegisterBlueprintSpecialtyNativePath(const TCHAR* Path);
	/** True if NativeRoot matches any path registered via RegisterBlueprintSpecialtyNativePath (used by generic Blueprint rule and when resolving chain). */
	static bool IsNativePathHandledBySpecialtyRule(const FString& NativeRoot);

	/** True if any of the rule paths is under one of the selected paths (so we only validate that folder). */
	static bool IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths);
	static bool IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths);

	/** True if path is under a folder exclusion or equals a file exclusion. Used by rules and tests. */
	static bool IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders);

	/**
	 * Returns the list of (QueryPath, OnlyAssetPaths) scopes to validate.
	 * Used by Validate_Implementation and by tests to assert folder/asset scope.
	 * ResolvedPaths: rule paths in Content form, with or without trailing slash.
	 * SelectedPaths: from menu; folder paths should end with / so only that folder is queried; asset paths without / restrict to that asset.
	 */
	static TArray<FAssetNamingScopeEntry> GetScopesForValidation(const TArray<FString>& ResolvedPaths, const TArray<FString>& SelectedPaths);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	static FString NormalizeRelativePath(const FString& InPath);
};
