// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionClassViewerOptions.h"
#include "ConventionKeeperConvention.h"
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"

namespace
{
	class FConventionClassFilter : public IClassViewerFilter
	{
	public:
		TSet<const UClass*> AllowedChildrenOfClasses;
		EClassFlags DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated;

		virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
		{
			return !InClass->HasAnyClassFlags(DisallowedClassFlags)
				&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
		}

		virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
		{
			return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
				&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
		}
	};
}

FClassViewerInitializationOptions FConventionClassViewerOptions::Build()
{
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::DisplayName;
	Options.bShowUnloadedBlueprints = true;
	Options.bEditorClassesOnly = false;
	TSharedPtr<FConventionClassFilter> Filter = MakeShareable(new FConventionClassFilter);
	Filter->AllowedChildrenOfClasses.Add(UConventionKeeperConvention::StaticClass());
	Options.ClassFilters.Add(Filter.ToSharedRef());
	return Options;
}
