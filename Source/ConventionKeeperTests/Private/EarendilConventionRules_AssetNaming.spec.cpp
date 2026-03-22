// Pavel Penkov 2025 All Rights Reserved.

#include "AssetRegistry/AssetData.h"
#include "Misc/AutomationTest.h"
#include "EarendilConvention/Rules/EarendilConventionRule_AssetNaming_StateTree.h"

#if WITH_DEV_AUTOMATION_TESTS

static FAssetData MakeSyntheticAssetDataEarendil(const FString& PackagePath, const FString& AssetName, const FString& ClassPath)
{
	const FString LongPackageName = PackagePath.StartsWith(TEXT("/")) ? PackagePath : (TEXT("/Game/") + PackagePath);
	const FString ObjectPath = LongPackageName + TEXT(".") + AssetName;
	const FTopLevelAssetPath ClassPathTop = FTopLevelAssetPath(ClassPath);
	return FAssetData(LongPackageName, ObjectPath, ClassPathTop, FAssetDataTagMap(), TArrayView<const int32>(), 0u);
}

BEGIN_DEFINE_SPEC(EarendilConventionRules_AssetNamingSpec,
	"ConventionKeeper.EarendilConventionRules.AssetNaming",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(EarendilConventionRules_AssetNamingSpec)

void EarendilConventionRules_AssetNamingSpec::Define()
{
	Describe("Earendil StateTree naming rule (EvaluateSingleAssetNaming)", [this]()
	{
		It("requires ST_ prefix for StateTreeModule.StateTree", [this]()
		{
			UEarendilConventionRule_AssetNaming_StateTree* Rule = NewObject<UEarendilConventionRule_AssetNaming_StateTree>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule)
			{
				return;
			}

			TMap<FString, FString> Placeholders;
			bool bValid = true;
			FString ExpectedPrefix;

			FAssetData Bad = MakeSyntheticAssetDataEarendil(TEXT("/Game/Test/NewStateTree"), TEXT("NewStateTree"), TEXT("/Script/StateTreeModule.StateTree"));
			Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, &ExpectedPrefix, nullptr);
			TestFalse(TEXT("Missing ST_ should be invalid"), bValid);
			TestEqual(TEXT("Expected prefix"), ExpectedPrefix, FString(TEXT("ST_")));

			FAssetData Good = MakeSyntheticAssetDataEarendil(TEXT("/Game/Test/ST_NewStateTree"), TEXT("ST_NewStateTree"), TEXT("/Script/StateTreeModule.StateTree"));
			Rule->EvaluateSingleAssetNaming(Good, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("ST_ prefix should be valid"), bValid);
		});

		It("requires ST_ prefix for StateTreeEditorModule.StateTree", [this]()
		{
			UEarendilConventionRule_AssetNaming_StateTree* Rule = NewObject<UEarendilConventionRule_AssetNaming_StateTree>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule)
			{
				return;
			}

			TMap<FString, FString> Placeholders;
			bool bValid = true;

			FAssetData Bad = MakeSyntheticAssetDataEarendil(TEXT("/Game/Test/MyStateTree"), TEXT("MyStateTree"), TEXT("/Script/StateTreeEditorModule.StateTree"));
			Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, nullptr, nullptr);
			TestFalse(TEXT("Missing ST_ should be invalid"), bValid);

			FAssetData Good = MakeSyntheticAssetDataEarendil(TEXT("/Game/Test/ST_MyStateTree"), TEXT("ST_MyStateTree"), TEXT("/Script/StateTreeEditorModule.StateTree"));
			Rule->EvaluateSingleAssetNaming(Good, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("ST_ prefix should be valid"), bValid);
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
