// Pavel Penkov 2025 All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "Rules/ConventionKeeperRule_NamingConvention.h"
#include "Rules/ConventionKeeperRule_NamingConvention_PascalCase.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionKeeperRule_NamingConvention_PascalCaseSpec,
	"ConventionKeeper.NamingConvention.PascalCase",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(ConventionKeeperRule_NamingConvention_PascalCaseSpec)

void ConventionKeeperRule_NamingConvention_PascalCaseSpec::Define()
{
	Describe("IsPascalCaseName", [this]()
	{
		It("rejects empty string", [this]()
		{
			TestFalse(TEXT("Empty"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(FString()));
		});

		It("accepts single segment starting with uppercase", [this]()
		{
			TestTrue(TEXT("MyFolder"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("MyFolder")));
			TestTrue(TEXT("M"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("M")));
			TestTrue(TEXT("Characters"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("Characters")));
			TestTrue(TEXT("Asset1"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("Asset1")));
		});

		It("rejects single segment starting with lowercase", [this]()
		{
			TestFalse(TEXT("myFolder"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("myFolder")));
			TestFalse(TEXT("asset"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("asset")));
		});

		It("accepts multiple segments with underscore (prefix + name)", [this]()
		{
			TestTrue(TEXT("BP_MyActor"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("BP_MyActor")));
			TestTrue(TEXT("M_MyMaterial"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("M_MyMaterial")));
			TestTrue(TEXT("AS_Zombie_Jump_01"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("AS_Zombie_Jump_01")));
		});

		It("accepts acronym segments (all caps)", [this]()
		{
			TestTrue(TEXT("BP"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("BP")));
			TestTrue(TEXT("BP_Player"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("BP_Player")));
			TestTrue(TEXT("SK_Character"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("SK_Character")));
		});

		It("rejects segment with leading lowercase after underscore", [this]()
		{
			TestFalse(TEXT("BP_myActor"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("BP_myActor")));
			TestFalse(TEXT("My_asset"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("My_asset")));
		});

		It("rejects empty segment (double underscore)", [this]()
		{
			TestFalse(TEXT("My__Folder"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("My__Folder")));
			TestFalse(TEXT("_MyFolder"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("_MyFolder")));
			TestFalse(TEXT("MyFolder_"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("MyFolder_")));
		});

		It("rejects segment with invalid characters", [this]()
		{
			TestFalse(TEXT("My-Folder"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("My-Folder")));
			TestFalse(TEXT("My Folder"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("My Folder")));
		});

		It("accepts digits after first character in segment", [this]()
		{
			TestTrue(TEXT("Asset01"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("Asset01")));
			TestTrue(TEXT("BP_Jump_99"), UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(TEXT("BP_Jump_99")));
		});
	});

	Describe("IsRelevantPath (NamingConvention base)", [this]()
	{
		It("returns true when no paths selected", [this]()
		{
			TArray<FString> Empty;
			TestTrue(TEXT("Relevant when no selection"),
				UConventionKeeperRule_NamingConvention::IsRelevantPath(TEXT("Content/GameCode/"), Empty));
		});

		It("returns true when rule path is under selected path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/"));
			TestTrue(TEXT("Rule path under selected"),
				UConventionKeeperRule_NamingConvention::IsRelevantPath(TEXT("Content/GameCode/Characters/"), Selected));
		});

		It("returns true when selected path is under rule path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/"));
			TestTrue(TEXT("Selected under rule path"),
				UConventionKeeperRule_NamingConvention::IsRelevantPath(TEXT("Content/GameCode/"), Selected));
		});

		It("returns false when rule path is not under selected path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Maps/"));
			TestFalse(TEXT("Unrelated selected path"),
				UConventionKeeperRule_NamingConvention::IsRelevantPath(TEXT("Content/GameCode/Characters/"), Selected));
		});
	});

	Describe("IsPathUnderExcluded (NamingConvention base)", [this]()
	{
		It("returns true when path is under folder exclusion", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Characters/"));
			TMap<FString, FString> Placeholders;
			TestTrue(TEXT("Path under excluded folder"),
				UConventionKeeperRule_NamingConvention::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/Animations/"), Exclusions, Placeholders));
		});

		It("returns false when path is not under any exclusion", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Maps/"));
			TMap<FString, FString> Placeholders;
			TestFalse(TEXT("Path not excluded"),
				UConventionKeeperRule_NamingConvention::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/"), Exclusions, Placeholders));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
