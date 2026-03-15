// Pavel Penkov 2025 All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "Commandlets/ConventionKeeperCommandlet.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionKeeperRule_AssetNamingSpec,
	"ConventionKeeper.AssetNaming",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(ConventionKeeperRule_AssetNamingSpec)

void ConventionKeeperRule_AssetNamingSpec::Define()
{
	Describe("ResolveNamingTemplate", [this]()
	{
		It("replaces single placeholder", [this]()
		{
			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("CharacterName"), TEXT("Zombie"));
			FString Result = UConventionKeeperRule_AssetNaming::ResolveNamingTemplate(TEXT("AS_{CharacterName}_"), Placeholders);
			TestEqual(TEXT("Resolved to AS_Zombie_"), Result, FString(TEXT("AS_Zombie_")));
		});

		It("replaces multiple placeholders", [this]()
		{
			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("CharacterName"), TEXT("Zombie"));
			Placeholders.Add(TEXT("Type"), TEXT("Anim"));
			FString Result = UConventionKeeperRule_AssetNaming::ResolveNamingTemplate(TEXT("AS_{CharacterName}_{Type}_"), Placeholders);
			TestEqual(TEXT("Resolved to AS_Zombie_Anim_"), Result, FString(TEXT("AS_Zombie_Anim_")));
		});

		It("leaves unknown placeholders as-is", [this]()
		{
			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("CharacterName"), TEXT("Zombie"));
			FString Result = UConventionKeeperRule_AssetNaming::ResolveNamingTemplate(TEXT("AS_{CharacterName}_{Other}_"), Placeholders);
			TestEqual(TEXT("{Other} unchanged"), Result, FString(TEXT("AS_Zombie_{Other}_")));
		});

		It("returns empty when template is empty", [this]()
		{
			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("CharacterName"), TEXT("Zombie"));
			FString Result = UConventionKeeperRule_AssetNaming::ResolveNamingTemplate(FString(), Placeholders);
			TestTrue(TEXT("Empty result"), Result.IsEmpty());
		});
	});

	Describe("IsNumberSuffixValid", [this]()
	{
		It("accepts name without numeric suffix", [this]()
		{
			TestTrue(TEXT("AS_Zombie_Jump"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump"), 2));
			TestTrue(TEXT("AS_Zombie_Jump_Final"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump_Final"), 2));
		});

		It("accepts zero-padded two-digit suffix", [this]()
		{
			TestTrue(TEXT("AS_Zombie_Jump_01"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump_01"), 2));
			TestTrue(TEXT("AS_Zombie_Jump_99"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump_99"), 2));
		});

		It("rejects single-digit suffix when padding is 2", [this]()
		{
			TestFalse(TEXT("AS_Zombie_Jump_1"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump_1"), 2));
		});

		It("rejects trailing digit without underscore (e.g. Grenade2) when padding is 2", [this]()
		{
			TestFalse(TEXT("AS_Player_Toss_Grenade2"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Player_Toss_Grenade2"), 2));
			TestFalse(TEXT("Grenade2"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("Grenade2"), 2));
		});

		It("rejects three-digit suffix when padding is 2", [this]()
		{
			TestFalse(TEXT("AS_Zombie_Jump_100"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump_100"), 2));
		});

		It("accepts three-digit suffix when padding is 3", [this]()
		{
			TestTrue(TEXT("AS_Zombie_Jump_001"), UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(TEXT("AS_Zombie_Jump_001"), 3));
		});
	});

	Describe("SuggestZeroPaddedName", [this]()
	{
		It("pads single digit to two digits", [this]()
		{
			FString Result = UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(TEXT("AS_Zombie_Jump_1"), 2);
			TestEqual(TEXT("AS_Zombie_Jump_01"), Result, FString(TEXT("AS_Zombie_Jump_01")));
		});

		It("leaves already-padded name unchanged", [this]()
		{
			FString Result = UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(TEXT("AS_Zombie_Jump_01"), 2);
			TestEqual(TEXT("AS_Zombie_Jump_01"), Result, FString(TEXT("AS_Zombie_Jump_01")));
		});

		It("pads to three digits when requested", [this]()
		{
			FString Result = UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(TEXT("AS_Zombie_Jump_5"), 3);
			TestEqual(TEXT("AS_Zombie_Jump_005"), Result, FString(TEXT("AS_Zombie_Jump_005")));
		});

		It("returns name unchanged when no trailing number", [this]()
		{
			FString Result = UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(TEXT("AS_Zombie_Jump"), 2);
			TestEqual(TEXT("AS_Zombie_Jump"), Result, FString(TEXT("AS_Zombie_Jump")));
		});

		It("inserts underscore and pads when trailing digit has no underscore (Grenade2 -> Grenade_02)", [this]()
		{
			FString Result = UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(TEXT("AS_Player_Toss_Grenade2"), 2);
			TestEqual(TEXT("AS_Player_Toss_Grenade_02"), Result, FString(TEXT("AS_Player_Toss_Grenade_02")));
			Result = UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(TEXT("Grenade2"), 2);
			TestEqual(TEXT("Grenade_02"), Result, FString(TEXT("Grenade_02")));
		});
	});

	Describe("ExtractPathPlaceholders", [this]()
	{
		It("extracts template placeholder from path", [this]()
		{
			TMap<FString, FString> GlobalPlaceholders;
			GlobalPlaceholders.Add(TEXT("{ProjectName}"), TEXT("GameCode"));
			TMap<FString, FString> OutPathPlaceholders;
			bool bOk = UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(
				TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations"),
				TEXT("Content/GameCode/Characters/Zombie/Animations"),
				GlobalPlaceholders,
				OutPathPlaceholders);
			TestTrue(TEXT("Extract succeeded"), bOk);
			TestTrue(TEXT("Has CharacterName"), OutPathPlaceholders.Contains(TEXT("CharacterName")));
			TestEqual(TEXT("CharacterName=Zombie"), OutPathPlaceholders[TEXT("CharacterName")], FString(TEXT("Zombie")));
		});

		It("returns false when segment count differs", [this]()
		{
			TMap<FString, FString> GlobalPlaceholders;
			TMap<FString, FString> OutPathPlaceholders;
			bool bOk = UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(
				TEXT("Content/{ProjectName}/Characters"),
				TEXT("Content/GameCode/Characters/Zombie"),
				GlobalPlaceholders,
				OutPathPlaceholders);
			TestFalse(TEXT("Extract fails on mismatch"), bOk);
		});

		It("returns false when global placeholder value does not match", [this]()
		{
			TMap<FString, FString> GlobalPlaceholders;
			GlobalPlaceholders.Add(TEXT("{ProjectName}"), TEXT("OtherProject"));
			TMap<FString, FString> OutPathPlaceholders;
			bool bOk = UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(
				TEXT("Content/{ProjectName}/Characters"),
				TEXT("Content/GameCode/Characters"),
				GlobalPlaceholders,
				OutPathPlaceholders);
			TestFalse(TEXT("Extract fails when global placeholder mismatch"), bOk);
		});
	});

	Describe("IsRelevantPath", [this]()
	{
		It("returns true when no paths selected (validate all)", [this]()
		{
			TArray<FString> Empty;
			TestTrue(TEXT("Relevant when no selection"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/Animations/"), Empty));
		});

		It("returns true when rule path is under selected path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/"));
			TestTrue(TEXT("Rule path under selected"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/Animations/"), Selected));
		});

		It("returns true when rule path is under selected path (validate in nested folder)", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/"));
			const FString ConcreteRulePath = TEXT("Content/GameCode/Characters/Player/Animations/");
			TestTrue(TEXT("Rule path under selected"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(ConcreteRulePath, Selected));
		});

		It("returns true when selected path is subfolder of rule path (validate only that folder)", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/"));
			const FString RulePath = TEXT("Content/GameCode/Characters/Player/Animations/");
			TestTrue(TEXT("Selected subfolder under rule path is relevant"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(RulePath, Selected));
		});

		It("returns false when rule path is not under selected path", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Maps/"));
			TestFalse(TEXT("Unrelated selected path"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/Animations/"), Selected));
		});

		It("returns true when selected path is a single asset path (validate specific file) and resolved path is that asset", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/MyAsset"));
			TestTrue(TEXT("Exact asset path is relevant when selected"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/MyAsset/"), Selected));
		});

		It("returns false when selected path is a single asset path and resolved path is another asset in same folder", [this]()
		{
			TArray<FString> Selected;
			Selected.Add(TEXT("Content/GameCode/Characters/Player/MyAsset"));
			TestFalse(TEXT("Other asset in same folder not relevant when only one asset selected"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(TEXT("Content/GameCode/Characters/Player/OtherAsset/"), Selected));
		});
	});

	Describe("GetScopesForValidation", [this]()
	{
		It("folder with trailing slash scopes only that folder", [this]()
		{
			TArray<FString> ResolvedPaths;
			ResolvedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/"));
			TArray<FString> SelectedPaths;
			SelectedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/"));
			TArray<FAssetNamingScopeEntry> Scopes =
				UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedPaths, SelectedPaths);
			TestEqual(TEXT("Exactly one scope"), Scopes.Num(), 1);
			if (Scopes.Num() > 0)
			{
				TestEqual(TEXT("QueryPath is selected folder only"), Scopes[0].QueryPath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/")));
				TestTrue(TEXT("OnlyAssetPaths empty for folder"), Scopes[0].OnlyAssetPaths.Num() == 0);
			}
		});

		It("asset without trailing slash scopes parent folder with asset filter", [this]()
		{
			TArray<FString> ResolvedPaths;
			ResolvedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/"));
			TArray<FString> SelectedPaths;
			SelectedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/AS_1H_Swords_Walk_B"));
			TArray<FAssetNamingScopeEntry> Scopes =
				UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedPaths, SelectedPaths);
			TestEqual(TEXT("Exactly one scope"), Scopes.Num(), 1);
			if (Scopes.Num() > 0)
			{
				TestEqual(TEXT("QueryPath is 1H folder"), Scopes[0].QueryPath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/")));
				TestEqual(TEXT("OnlyAssetPaths has 1"), Scopes[0].OnlyAssetPaths.Num(), 1);
				TestEqual(TEXT("OnlyAssetPaths[0]"), Scopes[0].OnlyAssetPaths[0],
					FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/AS_1H_Swords_Walk_B")));
			}
		});

		It("no selected paths returns full rule path scope", [this]()
		{
			TArray<FString> ResolvedPaths;
			ResolvedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/"));
			TArray<FString> SelectedPaths;
			TArray<FAssetNamingScopeEntry> Scopes =
				UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedPaths, SelectedPaths);
			TestEqual(TEXT("One scope"), Scopes.Num(), 1);
			if (Scopes.Num() > 0)
			{
				TestEqual(TEXT("QueryPath is full rule path"), Scopes[0].QueryPath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations/")));
				TestTrue(TEXT("OnlyAssetPaths empty"), Scopes[0].OnlyAssetPaths.Num() == 0);
			}
		});

		It("ignores intermediate paths when only Animations-level paths passed (simulates real ResolveTemplatePaths filtering)", [this]()
		{
			TArray<FString> ResolvedPaths;
			ResolvedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/"));
			TArray<FString> SelectedPaths;
			SelectedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/AS_1H_Swords_Walk_B"));
			TArray<FAssetNamingScopeEntry> Scopes =
				UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedPaths, SelectedPaths);
			TestEqual(TEXT("Exactly one scope"), Scopes.Num(), 1);
			if (Scopes.Num() > 0)
			{
				TestEqual(TEXT("RulePath is Animations-level"), Scopes[0].RulePath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations")));
			}
		});
	});

	Describe("Full flow: folder from Content Browser", [this]()
	{
		It("/Game/GameCode/Characters/Player/Animations/Swords/Walk/1H produces correct scope", [this]()
		{
			const FString ContentBrowserFolderPath = TEXT("/Game/GameCode/Characters/Player/Animations/Swords/Walk/1H");
			FString NormalizedFolder = ContentBrowserFolderPath;
			NormalizedFolder.ReplaceInline(TEXT("\\"), TEXT("/"));
			if (!NormalizedFolder.EndsWith(TEXT("/")))
			{
				NormalizedFolder += TEXT("/");
			}
			FString SelectedPath = UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(NormalizedFolder);
			TestEqual(TEXT("Folder path normalized to Content form"),
				SelectedPath,
				FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/")));
			TestTrue(TEXT("Ends with slash"), SelectedPath.EndsWith(TEXT("/")));
			TArray<FString> ResolvedPaths;
			ResolvedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/"));
			TArray<FString> SelectedPaths;
			SelectedPaths.Add(SelectedPath);
			TestTrue(TEXT("IsRelevantPath returns true"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(ResolvedPaths, SelectedPaths));
			TArray<FAssetNamingScopeEntry> Scopes =
				UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedPaths, SelectedPaths);
			TestEqual(TEXT("Exactly one scope"), Scopes.Num(), 1);
			if (Scopes.Num() > 0)
			{
				TestEqual(TEXT("QueryPath is Walk/1H folder"), Scopes[0].QueryPath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/")));
				TestTrue(TEXT("No asset filter (folder mode)"), Scopes[0].OnlyAssetPaths.IsEmpty());
				TestEqual(TEXT("RulePath is Animations"), Scopes[0].RulePath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations")));
				TMap<FString, FString> GlobalPlaceholders;
				GlobalPlaceholders.Add(TEXT("{ProjectName}"), TEXT("GameCode"));
				TMap<FString, FString> PathPlaceholders;
				bool bOk = UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(
					TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations"),
					Scopes[0].RulePath,
					GlobalPlaceholders,
					PathPlaceholders);
				TestTrue(TEXT("ExtractPathPlaceholders succeeds on scope RulePath"), bOk);
				if (bOk)
				{
					TestEqual(TEXT("CharacterName=Player"), PathPlaceholders[TEXT("CharacterName")], FString(TEXT("Player")));
				}
			}
		});
	});

	Describe("Full flow: asset from Content Browser", [this]()
	{
		It("/Game/.../AS_1H_Swords_Walk_B produces correct scope", [this]()
		{
			const FString PackageName = TEXT("/Game/GameCode/Characters/Player/Animations/Swords/Walk/1H/AS_1H_Swords_Walk_B");
			FString SelectedPath = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(PackageName, false);
			TestEqual(TEXT("Asset path normalized to Content form without trailing slash"),
				SelectedPath,
				FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/AS_1H_Swords_Walk_B")));
			TestFalse(TEXT("No trailing slash"), SelectedPath.EndsWith(TEXT("/")));
			TArray<FString> ResolvedPaths;
			ResolvedPaths.Add(TEXT("Content/GameCode/Characters/Player/Animations/"));
			TArray<FString> SelectedPaths;
			SelectedPaths.Add(SelectedPath);
			TestTrue(TEXT("IsRelevantPath returns true"),
				UConventionKeeperRule_AssetNaming::IsRelevantPath(ResolvedPaths, SelectedPaths));
			TArray<FAssetNamingScopeEntry> Scopes =
				UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedPaths, SelectedPaths);
			TestEqual(TEXT("Exactly one scope"), Scopes.Num(), 1);
			if (Scopes.Num() > 0)
			{
				TestEqual(TEXT("QueryPath is 1H folder"), Scopes[0].QueryPath,
					FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/")));
				TestEqual(TEXT("OnlyAssetPaths has one entry"), Scopes[0].OnlyAssetPaths.Num(), 1);
				if (Scopes[0].OnlyAssetPaths.Num() > 0)
				{
					TestEqual(TEXT("OnlyAssetPaths[0] is the asset"), Scopes[0].OnlyAssetPaths[0],
						FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Walk/1H/AS_1H_Swords_Walk_B")));
				}
				TMap<FString, FString> GlobalPlaceholders;
				GlobalPlaceholders.Add(TEXT("{ProjectName}"), TEXT("GameCode"));
				TMap<FString, FString> PathPlaceholders;
				bool bOk = UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(
					TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations"),
					Scopes[0].RulePath,
					GlobalPlaceholders,
					PathPlaceholders);
				TestTrue(TEXT("ExtractPathPlaceholders succeeds"), bOk);
				if (bOk)
				{
					TestEqual(TEXT("CharacterName=Player"), PathPlaceholders[TEXT("CharacterName")], FString(TEXT("Player")));
				}
			}
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
				UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/MyAsset"), Exclusions, Placeholders));
		});

		It("returns false when path is different asset and only file exclusion exists", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Characters/Player/MyAsset"));
			TMap<FString, FString> Placeholders;
			TestFalse(TEXT("Other asset not excluded"),
				UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/OtherAsset"), Exclusions, Placeholders));
		});

		It("returns true when path is under folder exclusion", [this]()
		{
			TArray<FString> Exclusions;
			Exclusions.Add(TEXT("Content/GameCode/Characters/Player/"));
			TMap<FString, FString> Placeholders;
			TestTrue(TEXT("Asset under excluded folder is excluded"),
				UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(TEXT("Content/GameCode/Characters/Player/MyAsset"), Exclusions, Placeholders));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
