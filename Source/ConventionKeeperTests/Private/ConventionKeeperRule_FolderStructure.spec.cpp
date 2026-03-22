// Pavel Penkov 2025 All Rights Reserved.

#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Rules/ConventionKeeperRule.h"
#include "Rules/ConventionKeeperRule_FolderStructure.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionKeeperRule_FolderStructureSpec,
	"ConventionKeeper.FolderStructure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	FString ScratchDirectoryAbsolute;

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

	Describe("CanValidate with FolderPath slash variants", [this]()
	{
		It("returns true for placeholder FolderPath with trailing slash", [this]()
		{
			UConventionKeeperRule_FolderStructure* Rule = NewObject<UConventionKeeperRule_FolderStructure>();
			Rule->FolderPath.Path = TEXT("Content/{ProjectName}/Inventory/");

			TArray<FString> SelectedPaths;
			SelectedPaths.Add(TEXT("/Game/GameCode/Inventory/"));

			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("ProjectName"), TEXT("GameCode"));

			TestTrue(TEXT("CanValidate should work with trailing slash in FolderPath"),
				Rule->CanValidate(SelectedPaths, Placeholders));
		});

		It("returns true for placeholder FolderPath without trailing slash", [this]()
		{
			UConventionKeeperRule_FolderStructure* Rule = NewObject<UConventionKeeperRule_FolderStructure>();
			Rule->FolderPath.Path = TEXT("Content/{ProjectName}/Inventory");

			TArray<FString> SelectedPaths;
			SelectedPaths.Add(TEXT("/Game/GameCode/Inventory/"));

			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("ProjectName"), TEXT("GameCode"));

			TestTrue(TEXT("CanValidate should work without trailing slash in FolderPath"),
				Rule->CanValidate(SelectedPaths, Placeholders));
		});
	});

	Describe("ResolvePlaceholdersForPath", [this]()
	{
		It("resolves placeholders in asset name patterns", [this]()
		{
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{CharacterName}"), TEXT("Skeleton"));
			const FString R = UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(TEXT("Gym_{CharacterName}"), Merged);
			TestEqual(TEXT("Gym_Skeleton"), R, FString(TEXT("Gym_Skeleton")));
		});

		It("resolves AIGym and suffix patterns", [this]()
		{
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{CharacterName}"), TEXT("Zombie"));
			TestEqual(TEXT("AIGym"),
				UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(TEXT("AIGym_{CharacterName}"), Merged),
				FString(TEXT("AIGym_Zombie")));
			TestEqual(TEXT("Arena"),
				UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(TEXT("AIGym_{CharacterName}_Arena"), Merged),
				FString(TEXT("AIGym_Zombie_Arena")));
		});
	});

	Describe("CollectAssetBaseNamesInDirectory", [this]()
	{
		BeforeEach([this]()
		{
			ScratchDirectoryAbsolute = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("ConventionKeeper_FolderStructure_AssetCollectSpec"));
			IFileManager::Get().DeleteDirectory(*ScratchDirectoryAbsolute, false, true);
			IFileManager::Get().MakeDirectory(*ScratchDirectoryAbsolute, true);
		});

		AfterEach([this]()
		{
			IFileManager::Get().DeleteDirectory(*ScratchDirectoryAbsolute, false, true);
		});

		It("collects only top-level uasset and umap base names", [this]()
		{
			TestTrue(TEXT("Save A.uasset"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("A.uasset"))));
			TestTrue(TEXT("Save B.umap"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("B.umap"))));
			TestTrue(TEXT("Save ignore.txt"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("ignore.txt"))));
			const FString SubDir = ScratchDirectoryAbsolute / TEXT("Nested");
			IFileManager::Get().MakeDirectory(*SubDir, true);
			TestTrue(TEXT("Save Nested/C.uasset"), FFileHelper::SaveStringToFile(TEXT(""), *(SubDir / TEXT("C.uasset"))));

			TSet<FName> Names;
			UConventionKeeperRule_FolderStructure::CollectAssetBaseNamesInDirectory(ScratchDirectoryAbsolute, Names);
			TestEqual(TEXT("two entries"), Names.Num(), 2);
			TestTrue(TEXT("A"), Names.Contains(FName(TEXT("A"))));
			TestTrue(TEXT("B"), Names.Contains(FName(TEXT("B"))));
			TestFalse(TEXT("no C from subfolder"), Names.Contains(FName(TEXT("C"))));
		});
	});

	Describe("GatherRequiredBannedAssetViolations", [this]()
	{
		BeforeEach([this]()
		{
			ScratchDirectoryAbsolute = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("ConventionKeeper_FolderStructure_GatherSpec"));
			IFileManager::Get().DeleteDirectory(*ScratchDirectoryAbsolute, false, true);
			IFileManager::Get().MakeDirectory(*ScratchDirectoryAbsolute, true);
		});

		AfterEach([this]()
		{
			IFileManager::Get().DeleteDirectory(*ScratchDirectoryAbsolute, false, true);
		});

		It("reports no violations when required files exist and banned absent", [this]()
		{
			TestTrue(TEXT("NeedA"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("NeedA.uasset"))));
			TestTrue(TEXT("NeedB"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("NeedB.umap"))));

			TArray<FString> Required = { TEXT("NeedA"), TEXT("NeedB") };
			TArray<FString> Banned = { TEXT("BadOne") };
			TMap<FString, FString> Merged;

			TArray<FString> Missing;
			TArray<FString> BannedHits;
			UConventionKeeperRule_FolderStructure::GatherRequiredBannedAssetViolations(
				ScratchDirectoryAbsolute,
				TEXT("Content/TestProj/Box/"),
				Required,
				Banned,
				Merged,
				Missing,
				BannedHits);

			TestEqual(TEXT("no missing"), Missing.Num(), 0);
			TestEqual(TEXT("no banned hits"), BannedHits.Num(), 0);
		});

		It("reports missing required assets with full Content-relative paths", [this]()
		{
			TArray<FString> Required = { TEXT("NeedX"), TEXT("Gym_{CharacterName}") };
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{CharacterName}"), TEXT("Hero"));

			TArray<FString> Missing;
			TArray<FString> BannedHits;
			UConventionKeeperRule_FolderStructure::GatherRequiredBannedAssetViolations(
				ScratchDirectoryAbsolute,
				TEXT("Content/MyGame/Characters/Hero/Gyms"),
				Required,
				TArray<FString>(),
				Merged,
				Missing,
				BannedHits);

			TestEqual(TEXT("two missing"), Missing.Num(), 2);
			TestTrue(TEXT("NeedX path"), Missing.Contains(TEXT("Content/MyGame/Characters/Hero/Gyms/NeedX")));
			TestTrue(TEXT("Gym_Hero path"), Missing.Contains(TEXT("Content/MyGame/Characters/Hero/Gyms/Gym_Hero")));
			TestEqual(TEXT("no banned"), BannedHits.Num(), 0);
		});

		It("skips patterns that still contain unresolved braces", [this]()
		{
			TestTrue(TEXT("OnlyReal.uasset"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("OnlyReal.uasset"))));

			TArray<FString> Required = { TEXT("OnlyReal"), TEXT("Gym_{UnknownPlaceholder}") };
			TMap<FString, FString> Merged;

			TArray<FString> Missing;
			TArray<FString> BannedHits;
			UConventionKeeperRule_FolderStructure::GatherRequiredBannedAssetViolations(
				ScratchDirectoryAbsolute,
				TEXT("Content/P/Gyms"),
				Required,
				TArray<FString>(),
				Merged,
				Missing,
				BannedHits);

			TestEqual(TEXT("unresolved pattern ignored"), Missing.Num(), 0);
		});

		It("reports present banned assets", [this]()
		{
			TestTrue(TEXT("Bad.uasset"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("Bad.uasset"))));
			TestTrue(TEXT("AlsoBad_X.umap"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("AlsoBad_X.umap"))));

			TArray<FString> Banned = { TEXT("Bad"), TEXT("AlsoBad_{Suffix}") };
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{Suffix}"), TEXT("X"));

			TArray<FString> Missing;
			TArray<FString> BannedHits;
			UConventionKeeperRule_FolderStructure::GatherRequiredBannedAssetViolations(
				ScratchDirectoryAbsolute,
				TEXT("Content/P/Folder"),
				TArray<FString>(),
				Banned,
				Merged,
				Missing,
				BannedHits);

			TestEqual(TEXT("no missing"), Missing.Num(), 0);
			TestEqual(TEXT("two banned"), BannedHits.Num(), 2);
			TestTrue(TEXT("Bad path"), BannedHits.Contains(TEXT("Content/P/Folder/Bad")));
			TestTrue(TEXT("AlsoBad_X path"), BannedHits.Contains(TEXT("Content/P/Folder/AlsoBad_X")));
		});
	});

	Describe("GatherDisallowedExtraAssets", [this]()
	{
		BeforeEach([this]()
		{
			ScratchDirectoryAbsolute = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("ConventionKeeper_FolderStructure_ExtraAssetsSpec"));
			IFileManager::Get().DeleteDirectory(*ScratchDirectoryAbsolute, false, true);
			IFileManager::Get().MakeDirectory(*ScratchDirectoryAbsolute, true);
		});

		AfterEach([this]()
		{
			IFileManager::Get().DeleteDirectory(*ScratchDirectoryAbsolute, false, true);
		});

		It("returns empty when on-disk assets match required set exactly", [this]()
		{
			TestTrue(TEXT("A"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("A.uasset"))));
			TestTrue(TEXT("B"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("B.umap"))));

			TArray<FString> Required = { TEXT("A"), TEXT("B") };
			TMap<FString, FString> Merged;

			TArray<FString> Extras;
			UConventionKeeperRule_FolderStructure::GatherDisallowedExtraAssets(
				ScratchDirectoryAbsolute,
				TEXT("Content/X/Box"),
				Required,
				Merged,
				Extras);

			TestEqual(TEXT("no extras"), Extras.Num(), 0);
		});

		It("lists every asset not in resolved RequiredAssets", [this]()
		{
			TestTrue(TEXT("Good"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("Good.uasset"))));
			TestTrue(TEXT("Stray"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("Stray.umap"))));

			TArray<FString> Required = { TEXT("Good") };
			TMap<FString, FString> Merged;

			TArray<FString> Extras;
			UConventionKeeperRule_FolderStructure::GatherDisallowedExtraAssets(
				ScratchDirectoryAbsolute,
				TEXT("Content/X/Box"),
				Required,
				Merged,
				Extras);

			TestEqual(TEXT("one extra"), Extras.Num(), 1);
			TestTrue(TEXT("Stray path"), Extras.Contains(TEXT("Content/X/Box/Stray")));
		});

		It("treats empty RequiredAssets as allowing none on disk", [this]()
		{
			TestTrue(TEXT("Only.uasset"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("Only.uasset"))));

			TArray<FString> Required;
			TMap<FString, FString> Merged;

			TArray<FString> Extras;
			UConventionKeeperRule_FolderStructure::GatherDisallowedExtraAssets(
				ScratchDirectoryAbsolute,
				TEXT("Content/X"),
				Required,
				Merged,
				Extras);

			TestEqual(TEXT("all files extra"), Extras.Num(), 1);
			TestTrue(TEXT("Only"), Extras.Contains(TEXT("Content/X/Only")));
		});

		It("resolves placeholders in required names before comparing", [this]()
		{
			TestTrue(TEXT("Gym_Hero"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("Gym_Hero.uasset"))));
			TestTrue(TEXT("Trash"), FFileHelper::SaveStringToFile(TEXT(""), *(ScratchDirectoryAbsolute / TEXT("Trash.umap"))));

			TArray<FString> Required = { TEXT("Gym_{CharacterName}") };
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{CharacterName}"), TEXT("Hero"));

			TArray<FString> Extras;
			UConventionKeeperRule_FolderStructure::GatherDisallowedExtraAssets(
				ScratchDirectoryAbsolute,
				TEXT("Content/P/Gyms"),
				Required,
				Merged,
				Extras);

			TestEqual(TEXT("Trash only"), Extras.Num(), 1);
			TestTrue(TEXT("Trash path"), Extras.Contains(TEXT("Content/P/Gyms/Trash")));
		});
	});

	Describe("Rule folder root match for RequiredAssets", [this]()
	{
		It("does not treat parent character folder as rule root when FolderPath ends in Gyms", [this]()
		{
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{ProjectName}"), TEXT("GameCode"));
			Merged.Add(TEXT("{CharacterName}"), TEXT("Skeleton"));

			const FString FolderPath = TEXT("Content/GameCode/Characters/Skeleton/Gyms/");
			const FString WrongBase = TEXT("Content/GameCode/Characters/Skeleton/");
			const FString ExpectedResolved = UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(FolderPath, Merged);
			const FString ExpectedNorm = UConventionKeeperRule::NormalizeRelativePath(ExpectedResolved);
			const FString CurrentNorm = UConventionKeeperRule::NormalizeRelativePath(WrongBase);
			const bool bWouldRunAssetChecks = !ExpectedNorm.Contains(TEXT("{"))
				&& CurrentNorm.Equals(ExpectedNorm, ESearchCase::IgnoreCase);

			TestFalse(TEXT("parent folder must not match gym rule root"), bWouldRunAssetChecks);
		});

		It("treats resolved Gyms path as matching rule root", [this]()
		{
			TMap<FString, FString> Merged;
			Merged.Add(TEXT("{ProjectName}"), TEXT("GameCode"));
			Merged.Add(TEXT("{CharacterName}"), TEXT("Skeleton"));

			const FString FolderPath = TEXT("Content/GameCode/Characters/Skeleton/Gyms/");
			const FString RightBase = TEXT("Content/GameCode/Characters/Skeleton/Gyms/");
			const FString ExpectedResolved = UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(FolderPath, Merged);
			const FString ExpectedNorm = UConventionKeeperRule::NormalizeRelativePath(ExpectedResolved);
			const FString CurrentNorm = UConventionKeeperRule::NormalizeRelativePath(RightBase);
			const bool bWouldRunAssetChecks = !ExpectedNorm.Contains(TEXT("{"))
				&& CurrentNorm.Equals(ExpectedNorm, ESearchCase::IgnoreCase);

			TestTrue(TEXT("Gyms folder matches rule root"), bWouldRunAssetChecks);
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
