// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperBlueprintLibrary.h"
#include "Commandlets/ConventionKeeperCommandlet.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionSpec,
	"ConventionKeeper.Convention.Spec",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	FString RootDirAbsolute;
	FString RootDirRelative;
	TMap<FString, FString> GlobalPlaceholders;
	IFileManager& FM = IFileManager::Get();

END_DEFINE_SPEC(ConventionSpec)

void ConventionSpec::Define()
{
	Describe("ExtractTemplatesFromPath", [this]()
	{
		BeforeEach([this]()
		{
			GlobalPlaceholders = {
				{TEXT("{ProjectName}"), TEXT("TestProjectName")},
				{TEXT("{GameVersion}"), TEXT("v1")}
			};
		});

		It("returns an empty set when there are no {…} segments", [this]()
		{
			const FString Path = TEXT("/Game/Content/Static/Meshes");
			TSet<FString> Results = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
			TestTrue("Should be empty", Results.Num() == 0);
		});

		It("finds a single template and ignores placeholders", [this]()
		{
			const FString Path = TEXT("/{ProjectName}/{CharacterName}/Meshes");
			TSet<FString> Results = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
			TestTrue("Contains CharacterName", Results.Contains(TEXT("CharacterName")));
			TestFalse("Does not contain ProjectName", Results.Contains(TEXT("ProjectName")));
			TestEqual("Exactly one template", Results.Num(), 1);
		});

		It("finds multiple templates in one path", [this]()
		{
			const FString Path = TEXT("/UI/{WidgetType}/{SkinVariant}/Preview");
			TSet<FString> Results = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
			TestTrue("Contains WidgetType", Results.Contains(TEXT("WidgetType")));
			TestTrue("Contains SkinVariant", Results.Contains(TEXT("SkinVariant")));
			TestEqual("Two templates found", Results.Num(), 2);
		});

		It("handles braces but empty name gracefully", [this]()
		{
			const FString Path = TEXT("/Data/{}/Values/{LOD}");
			TSet<FString> Results = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
			TestTrue("Contains LOD", Results.Contains(TEXT("LOD")));
			TestFalse("Does not contain empty", Results.Contains(TEXT("")));
			TestEqual("One template found", Results.Num(), 1);
		});

		It("handles trailing and leading slashes correctly", [this]()
		{
			const FString Path = TEXT("{Global}/Start/{End}/");
			TSet<FString> Results = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
			TestTrue("Contains Global", Results.Contains(TEXT("Global")));
			TestTrue("Contains End", Results.Contains(TEXT("End")));
			TestEqual("Two templates found", Results.Num(), 2);
		});
	});

	Describe("ResolveTemplatePaths", [this]()
	{
		BeforeEach([this]()
		{
			RootDirAbsolute = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("TemplateUtilsResolveSpec"));
			FM.DeleteDirectory(*RootDirAbsolute, false, true);
			FM.MakeDirectory(*RootDirAbsolute, true);
			RootDirRelative = RootDirAbsolute;
			FPaths::MakePathRelativeTo(RootDirRelative, *FPaths::ProjectDir());
			RootDirRelative.ReplaceInline(TEXT("\\"), TEXT("/"));

			GlobalPlaceholders = {
				{TEXT("{ProjectName}"), TEXT("TestProjectName")},
				{TEXT("{GameVersion}"), TEXT("v1")}
			};
		});

		AfterEach([this]()
		{
			FM.DeleteDirectory(*RootDirAbsolute, false, true);
		});

		It("returns empty when the literal base folder does not exist", [this]()
		{
			FString Pattern = FPaths::Combine(RootDirRelative, TEXT("DoesNotExist"), TEXT("{Tpl}"));
			Pattern.ReplaceInline(TEXT("\\"), TEXT("/"));
			TArray<FString> Results = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(Pattern, GlobalPlaceholders);
			TestTrue(TEXT("No matches"), Results.Num() == 0);
		});

		It("resolves a single-level template", [this]()
		{
			const FString BaseAbs = FPaths::Combine(RootDirAbsolute, TEXT("RootFolder"));
			FString BaseRel = FPaths::Combine(RootDirRelative, TEXT("RootFolder"));
			BaseRel.ReplaceInline(TEXT("\\"), TEXT("/"));
			FM.MakeDirectory(*BaseAbs, true);
			for (const TCHAR* Sub : { TEXT("A"), TEXT("B") })
			{
				FM.MakeDirectory(*FPaths::Combine(BaseAbs, Sub), true);
			}

			FString Pattern = FPaths::Combine(RootDirRelative, TEXT("RootFolder"), TEXT("{Tpl}"));
			Pattern.ReplaceInline(TEXT("\\"), TEXT("/"));
			TArray<FString> Results = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(Pattern, GlobalPlaceholders);

			TestEqual(TEXT("Two matches expected"), Results.Num(), 2);
			for (const TCHAR* Sub : { TEXT("A"), TEXT("B") })
			{
				FString Expected = FString(TEXT("/")) + FPaths::Combine(RootDirRelative, TEXT("RootFolder"), Sub);
				Expected.ReplaceInline(TEXT("\\"), TEXT("/"));
				TestTrue(*FString::Printf(TEXT("Contains %s"), Sub), Results.Contains(Expected));
			}
		});

		It("resolves nested templates at multiple depths", [this]()
		{
			const FString BaseAbs = FPaths::Combine(RootDirAbsolute, TEXT("Base"));
			FString BaseRel = FPaths::Combine(RootDirRelative, TEXT("Base"));
			BaseRel.ReplaceInline(TEXT("\\"), TEXT("/"));
			FM.MakeDirectory(*BaseAbs, true);

			const FString T1Abs = FPaths::Combine(BaseAbs, TEXT("T1"));
			FM.MakeDirectory(*T1Abs, true);
			FM.MakeDirectory(*FPaths::Combine(T1Abs, TEXT("Sub1")), true);
			FM.MakeDirectory(*FPaths::Combine(T1Abs, TEXT("Sub2")), true);

			const FString T2Abs = FPaths::Combine(BaseAbs, TEXT("T2"));
			FM.MakeDirectory(*T2Abs, true);
			FM.MakeDirectory(*FPaths::Combine(T2Abs, TEXT("Sub3")), true);

			FString Pattern = FPaths::Combine(RootDirRelative, TEXT("Base"), TEXT("{Tpl1}"), TEXT("{Tpl2}"));
			Pattern.ReplaceInline(TEXT("\\"), TEXT("/"));
			TArray<FString> Results = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(Pattern, GlobalPlaceholders);

			TestEqual(TEXT("Five matches expected"), Results.Num(), 5);
			for (const TCHAR* Name : { TEXT("T1"), TEXT("T2"), TEXT("Sub1"), TEXT("Sub2"), TEXT("Sub3") })
			{
				bool bFound = false;
				for (const FString& R : Results)
				{
					if (R.EndsWith(Name))
					{
						bFound = true;
						break;
					}
				}
				TestTrue(*FString::Printf(TEXT("Contains %s"), Name), bFound);
			}
		});

		It("treats global placeholders like literals", [this]()
		{
			const FString BaseAbs = FPaths::Combine(RootDirAbsolute, TEXT("Root"));
			FM.MakeDirectory(*FPaths::Combine(BaseAbs, TEXT("TestProjectName")), true);
			FM.MakeDirectory(*FPaths::Combine(BaseAbs, TEXT("TestProjectName"), TEXT("X")), true);

			FString Pattern = FPaths::Combine(RootDirRelative, TEXT("Root"), TEXT("{ProjectName}"), TEXT("{Tpl}"));
			Pattern.ReplaceInline(TEXT("\\"), TEXT("/"));
			TArray<FString> Results = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(Pattern, GlobalPlaceholders);

			TestEqual(TEXT("One match expected"), Results.Num(), 1);
			FString Expected = FString(TEXT("/")) + FPaths::Combine(RootDirRelative, TEXT("Root"), TEXT("TestProjectName"), TEXT("X"));
			Expected.ReplaceInline(TEXT("\\"), TEXT("/"));
			TestTrue(TEXT("Contains X path"), Results.Contains(Expected));
		});

		It("resolves Content/ProjectName with global placeholder only", [this]()
		{
			TMap<FString, FString> Placeholders;
			Placeholders.Add(TEXT("{ProjectName}"), TEXT("GameCode"));
			const FString Pattern = TEXT("Content/{ProjectName}");
			TArray<FString> Results = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(Pattern, Placeholders);
			TestEqual(TEXT("One path when only global placeholder"), Results.Num(), 1);
			TestTrue(TEXT("Path contains Content/GameCode"), Results[0].Contains(TEXT("Content")) && Results[0].Contains(TEXT("GameCode")));
		});
	});

	Describe("Path normalization", [this]()
	{
		It("converts absolute folder path to Content form with slash", [this]()
		{
			const FString InPath = TEXT("P:/gamecode/Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light");
			const FString Result = UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(InPath);
			TestEqual(TEXT("Folder path normalized"), Result,
				FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/")));
		});

		It("converts absolute uasset path to file exclusion form without extension", [this]()
		{
			const FString InPath = TEXT("P:/gamecode/Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/AS_1H_Swords_Stagger_Light_B.uasset");
			const FString Result = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(InPath, false);
			TestEqual(TEXT("Asset path normalized for exclusion"), Result,
				FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/AS_1H_Swords_Stagger_Light_B")));
		});

		It("converts /All/Game folder path to Content form", [this]()
		{
			const FString InPath = TEXT("/All/Game/GameCode/Characters/Player/Animations/Swords/Staggers/Light");
			const FString Result = UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(InPath);
			TestEqual(TEXT("All/Game path normalized"), Result,
				FString(TEXT("Content/GameCode/Characters/Player/Animations/Swords/Staggers/Light/")));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
