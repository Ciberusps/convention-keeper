// Pavel Penkov 2025 All Rights Reserved.

#include "Factories/ConventionAssetFactory.h"
#include "ConventionKeeperConvention_Base.h"
#include "ConventionClassViewerOptions.h"
#include "Kismet2/SClassPickerDialog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionAssetFactory)

static UClass* GetDefaultConventionClass()
{
	static UClass* Cached = nullptr;
	if (!Cached)
	{
		Cached = LoadClass<UConventionKeeperConvention_Base>(nullptr, TEXT("/Script/ConventionKeeperConventions.EarendilConvention"));
		if (!Cached)
		{
			Cached = LoadClass<UConventionKeeperConvention_Base>(nullptr, TEXT("/Script/ConventionKeeperConventions.UE5StyleGuideConvention"));
		}
		if (!Cached)
		{
			Cached = UConventionKeeperConvention_Base::StaticClass();
		}
	}
	return Cached;
}

UConventionFactory::UConventionFactory()
{
	SupportedClass = UConventionKeeperConvention_Base::StaticClass();
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
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UConventionKeeperConvention_Base::StaticClass());

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
	UConventionKeeperConvention_Base* Convention = NewObject<UConventionKeeperConvention_Base>(
		InParent,
		UConventionKeeperConvention_Base::StaticClass(),
		Name,
		Flags | RF_Transactional);

	if (Convention)
	{
		UClass* ResolvedExtendsClass = ExtendsConventionClass.Get();
		if (!ResolvedExtendsClass)
		{
			ResolvedExtendsClass = GetDefaultConventionClass();
		}
		Convention->SetExtendsConventionClass(ResolvedExtendsClass);
	}
	return Convention;
}
