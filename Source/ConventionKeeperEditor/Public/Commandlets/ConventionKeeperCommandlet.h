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

	static bool ValidateData(TArrayView<const FString> Paths, bool bAssetPaths = false);

	/** Converts a content-browser or package path to Content/... form. If bFolder, adds trailing slash. */
	static FString ConvertPathToRelativeForValidation(const FString& InPath);
	static FString ConvertPathToRelativeForExclusion(const FString& InPath, bool bFolder);
};
