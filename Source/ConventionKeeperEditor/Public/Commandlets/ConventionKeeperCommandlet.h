// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"
#include "ConventionKeeperCommandlet.generated.h"

UCLASS()
class CONVENTIONKEEPEREDITOR_API UConventionKeeperCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UConventionKeeperCommandlet();

	// Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	// End UCommandlet Interface

	static bool ValidateData(TArrayView<const FString> Paths, bool bAssetPaths = false, const struct FConventionKeeperValidationHooks* ExternalHooks = nullptr);

	/**
	 * Folder validation batches: removes paths that are strict ancestors of another path in the list.
	 * Paths must be in Content/.../ form (as from ConvertPathToRelativeForValidation for folders).
	 * Batch helper: removes ancestor Content/ paths when a descendant is in the same list (avoids Asset Naming scope widening when parent+child appear together). Not applied inside ValidateData: Folder Structure matching often needs the parent path when the new folder is a sibling of rule roots (e.g. rule Content/.../Characters/ vs new Content/.../NewFolder/). Exposed for automation tests and future targeted use.
	 */
	static void PruneAncestorContentFolderPaths(TArray<FString>& InOutPaths);

	/** Converts a content-browser or package path to Content/... form. If bFolder, adds trailing slash. */
	static FString ConvertPathToRelativeForValidation(const FString& InPath);
	static FString ConvertPathToRelativeForExclusion(const FString& InPath, bool bFolder);

	/**
	 * After a folder or asset under /Game is removed, returns the parent folder package path with trailing slash
	 * (e.g. /Game/A/B/C -> /Game/A/B/). Empty if the parent would be content root only (/Game/).
	 */
	static FString GetParentGameFolderPackagePathForValidationQueue(const FString& InPath);

};
