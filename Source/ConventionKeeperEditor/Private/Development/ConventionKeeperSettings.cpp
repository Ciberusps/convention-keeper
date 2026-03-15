// Pavel Penkov 2025 All Rights Reserved.

#include "Development/ConventionKeeperSettings.h"

#include "Internationalization/Culture.h"
#include "Internationalization/Internationalization.h"
#include "UObject/UnrealType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperSettings)

UConventionKeeperSettings::UConventionKeeperSettings()
{
	Convention = nullptr;
	ProjectNameFolder = FApp::GetProjectName();
}

void UConventionKeeperSettings::PostLoad()
{
	Super::PostLoad();
	bConventionAssetIsSet = !ConventionAsset.IsNull();
	if (ProjectNameFolder.IsEmpty())
	{
		ProjectNameFolder = FApp::GetProjectName();
	}
}

void UConventionKeeperSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UConventionKeeperSettings, ConventionAsset))
	{
		bConventionAssetIsSet = !ConventionAsset.IsNull();
	}
}

UConventionKeeperConvention* UConventionKeeperSettings::GetResolvedConvention() const
{
	if (ConventionAsset.IsValid())
	{
		return ConventionAsset.Get();
	}
	if (Convention.Get())
	{
		return Convention->GetDefaultObject<UConventionKeeperConvention>();
	}
	return nullptr;
}

bool UConventionKeeperSettings::GetEffectiveValidationEnabled() const
{
	const UConventionKeeperLocalSettings* LocalSettings = GetDefault<UConventionKeeperLocalSettings>();
	if (LocalSettings && LocalSettings->LocalOverrideValidation != EConventionKeeperValidationOverride::UseProjectDefault)
	{
		return LocalSettings->LocalOverrideValidation == EConventionKeeperValidationOverride::Enabled;
	}
	return bValidationEnabled;
}

TMap<FString, FString> UConventionKeeperSettings::GetPlaceholders() const
{
	TMap<FString, FString> InternalPlaceholders = {
		{ "{ProjectName}", ProjectNameFolder }
	};
	InternalPlaceholders.Append(Placeholders);
	return InternalPlaceholders;
}

FString UConventionKeeperSettings::GetEffectiveLanguageCode() const
{
	const UConventionKeeperLocalSettings* LocalSettings = GetDefault<UConventionKeeperLocalSettings>();
	if (LocalSettings && LocalSettings->LocalOverrideLanguage != EConventionKeeperLanguageOverride::UseProjectDefault)
	{
		return LocalSettings->LocalOverrideLanguage == EConventionKeeperLanguageOverride::Russian ? TEXT("ru") : TEXT("en");
	}
	switch (DefaultLanguage)
	{
	case EConventionKeeperLanguage::English:
		return TEXT("en");
	case EConventionKeeperLanguage::Russian:
		return TEXT("ru");
	case EConventionKeeperLanguage::Auto:
	default:
		break;
	}
	FString Current = FInternationalization::Get().GetCurrentLanguage()->GetName();
	if (Current.StartsWith(TEXT("ru"), ESearchCase::IgnoreCase))
	{
		return TEXT("ru");
	}
	return TEXT("en");
}
