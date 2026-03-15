// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_NamingConvention.h"
#include "ConventionKeeperRule_NamingConvention_PascalCase.generated.h"

/**
 * Rule: folder and asset names must be PascalCase.
 * Each segment (after splitting by underscore) must start with an uppercase letter, rest alphanumeric lowercase/digits.
 * E.g. MyFolder, BP_MyActor, M_MyMaterial are valid; myFolder, bp_MyActor are not.
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule_NamingConvention_PascalCase : public UConventionKeeperRule_NamingConvention
{
	GENERATED_BODY()

public:
	UConventionKeeperRule_NamingConvention_PascalCase();

	bool IsNameValidForFolder_Implementation(const FString& Name) const override;
	bool IsNameValidForAsset_Implementation(const FString& Name) const override;

	/** Returns true if the name is valid PascalCase (each segment: [A-Z][a-z0-9]*). */
	static bool IsPascalCaseName(const FString& Name);
};
