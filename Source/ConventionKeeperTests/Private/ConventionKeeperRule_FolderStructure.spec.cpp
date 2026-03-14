// Pavel Penkov 2025 All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "Rules/ConventionKeeperRule_FolderStructure.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionKeeperRule_FolderStructureSpec,
	"ConventionKeeper.FolderStructure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(ConventionKeeperRule_FolderStructureSpec)

void ConventionKeeperRule_FolderStructureSpec::Define()
{
	Describe("IsRelevantPath", [this]()
	{
		It("returns true when no paths selected (validate all)", [this]()
		{
			TArray<FString> Empty;
			TestTrue(TEXT("Relevant when no selection"),
				UConventionKeeperRule_FolderStructure::IsRelevantPath(TEXT("Content/GameCode/Characters/"), Empty));
		});

		It("returns true when rule path is under selected path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/"));
			TestTrue(TEXT("Rule path under selected"),
				UConventionKeeperRule_FolderStructure::IsRelevantPath(TEXT("Content/GameCode/Characters/"), Selected));
		});

		It("returns true when rule path is under selected path (validate in nested folder)", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/"));
			const FString ConcreteRulePath = TEXT("Content/GameCode/Characters/Player/Animations/");
			TestTrue(TEXT("Rule path under selected"),
				UConventionKeeperRule_FolderStructure::IsRelevantPath(ConcreteRulePath, Selected));
		});

		It("returns true for /Game/ path when rule path is under selected", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("/Game/GameCode/Characters/Player"));
			const FString ConcreteRulePath = TEXT("Content/GameCode/Characters/Player/Animations/");
			TestTrue(TEXT("Selected /Game/ normalized; rule path under selected"),
				UConventionKeeperRule_FolderStructure::IsRelevantPath(ConcreteRulePath, Selected));
		});

		It("returns false when rule path is not under selected path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Maps/"));
			TestFalse(TEXT("Unrelated selected path"),
				UConventionKeeperRule_FolderStructure::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/Animations/"), Selected));
		});

		It("returns false when selected path is a single asset path (validate specific file) and resolved path is parent folder", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/MyAsset"));
			TestFalse(TEXT("Parent folder not relevant when only asset path selected"),
				UConventionKeeperRule_FolderStructure::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/"), Selected));
		});
	});

	Describe("IsPathUnderExcluded", [this]()
	{
		It("returns true when path equals file exclusion (specific file in exclusions)", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Characters/Player/MyAsset"));
			TMap<FString, FString> Placeholders;
			TestTrue(TEXT("Exact asset path is excluded"),
				UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/MyAsset"), Exclusions, Placeholders));
		});

		It("returns false when path is different asset and only file exclusion exists", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Characters/Player/MyAsset"));
			TMap<FString, FString> Placeholders;
			TestFalse(TEXT("Other asset not excluded"),
				UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/OtherAsset"), Exclusions, Placeholders));
		});

		It("returns true when path is under folder exclusion", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Characters/Player/"));
			TMap<FString, FString> Placeholders;
			TestTrue(TEXT("Folder under excluded folder is excluded"),
				UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/Animations/"), Exclusions, Placeholders));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
