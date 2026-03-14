// Pavel Penkov 2025 All Rights Reserved.

#include "Factories/ConventionAssetFactory.h"
#include "Convention.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionAssetFactory)

UConventionFactory::UConventionFactory()
{
	SupportedClass = UConvention::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UConventionFactory::FactoryCreateNew(
	UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	return NewObject<UConvention>(InParent, Class, Name, Flags | RF_Transactional);
}
