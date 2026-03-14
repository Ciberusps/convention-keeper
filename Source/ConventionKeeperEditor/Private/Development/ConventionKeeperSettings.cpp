// Pavel Penkov 2025 All Rights Reserved.

#include "Development/ConventionKeeperSettings.h"

#include "Conventions/UHLConvention/UHLConvention.h"
#include "UObject/UnrealType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperSettings)

UConventionKeeperSettings::UConventionKeeperSettings()
{
    Convention = UUHLConvention::StaticClass();
}

void UConventionKeeperSettings::PostLoad()
{
	Super::PostLoad();
	bConventionAssetIsSet = !ConventionAsset.IsNull();
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

TMap<FString, FString> UConventionKeeperSettings::GetPlaceholders() const
{
	TMap<FString, FString> InternalPlaceholders = {
		{ "{ProjectName}", ProjectNameFolder }
	};
	InternalPlaceholders.Append(Placeholders);
	return InternalPlaceholders;
}
