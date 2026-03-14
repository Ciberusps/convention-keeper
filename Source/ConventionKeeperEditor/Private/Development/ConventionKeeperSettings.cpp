// Pavel Penkov 2025 All Rights Reserved.

#include "Development/ConventionKeeperSettings.h"

#include "Conventions/UHLConvention/UHLConvention.h"
#include "Misc/ConfigCacheIni.h"
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
	if (Exclusions.Num() == 0)
	{
		TArray<FString> LegacyExcludeFolders;
		const FString ConfigFilename = GetDefaultConfigFilename();
		if (GConfig->GetArray(*GetClass()->GetPathName(), TEXT("ExcludeFolders"), LegacyExcludeFolders, ConfigFilename) && LegacyExcludeFolders.Num() > 0)
		{
			Exclusions = MoveTemp(LegacyExcludeFolders);
			SaveConfig(CPF_Config);
		}
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

TMap<FString, FString> UConventionKeeperSettings::GetPlaceholders() const
{
	TMap<FString, FString> InternalPlaceholders = {
		{ "{ProjectName}", ProjectNameFolder }
	};
	InternalPlaceholders.Append(Placeholders);
	return InternalPlaceholders;
}
