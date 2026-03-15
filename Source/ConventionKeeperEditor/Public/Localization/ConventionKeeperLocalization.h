// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"

class UConventionKeeperSettings;

namespace ConventionKeeperLoc
{
	/** Returns localized FText for the given key using Settings → Language (Auto/En/Ru). */
	CONVENTIONKEEPEREDITOR_API FText GetText(FName Key);

	/** Returns localized string for the given language code ("en" or "ru"). Used when Settings may be unavailable. */
	CONVENTIONKEEPEREDITOR_API FText GetTextForLanguage(FName Key, const FString& LanguageCode);
}
