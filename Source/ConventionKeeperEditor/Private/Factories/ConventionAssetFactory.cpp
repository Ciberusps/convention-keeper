// Pavel Penkov 2025 All Rights Reserved.

#include "Factories/ConventionAssetFactory.h"
#include "ConventionKeeperConvention.h"
#include "ConventionClassViewerOptions.h"
#include "Kismet2/SClassPickerDialog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionAssetFactory)

UConventionFactory::UConventionFactory()
{
	SupportedClass = UConventionKeeperConvention::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
	ExtendsConventionClass = nullptr;
}

bool UConventionFactory::ConfigureProperties()
{
	ExtendsConventionClass = nullptr;

	FClassViewerInitializationOptions Options = FConventionClassViewerOptions::Build();

	const FText TitleText = NSLOCTEXT("ConventionKeeper", "PickExtendsConvention", "Pick Convention To Extend (ExtendsConvention)");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UConventionKeeperConvention::StaticClass());

	if (bPressedOk && ChosenClass)
	{
		ExtendsConventionClass = ChosenClass;
	}

	return bPressedOk;
}

UObject* UConventionFactory::FactoryCreateNew(
	UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn)
{
	UConventionKeeperConvention* Convention = NewObject<UConventionKeeperConvention>(InParent, UConventionKeeperConvention::StaticClass(), Name, Flags | RF_Transactional);
	if (Convention && ExtendsConventionClass.Get())
	{
		Convention->ExtendsConvention = ExtendsConventionClass;
	}
	return Convention;
}
