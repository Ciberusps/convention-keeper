// Pavel Penkov 2025 All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintInterface.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Structure.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(UE5StyleGuideRules_AssetNamingSpec,
	"ConventionKeeper.UE5StyleGuide.AssetNamingRules",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(UE5StyleGuideRules_AssetNamingSpec)

void UE5StyleGuideRules_AssetNamingSpec::Define()
{
	Describe("Structure rule", [this]()
	{
		It("contains struct class paths needed for UE5.6 registry variants", [this]()
		{
			const UUE5StyleGuideRule_AssetNaming_Structure* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_Structure>(GetTransientPackage());
			TestNotNull(TEXT("Rule object created"), Rule);
			if (!Rule)
			{
				return;
			}

			TestTrue(TEXT("Contains /Script/Engine.UserDefinedStruct"), Rule->AssetClassPaths.Contains(TEXT("/Script/Engine.UserDefinedStruct")));
			TestTrue(TEXT("Contains /Script/CoreUObject.UserDefinedStruct"), Rule->AssetClassPaths.Contains(TEXT("/Script/CoreUObject.UserDefinedStruct")));
			TestTrue(TEXT("Contains /Script/CoreUObject.ScriptStruct"), Rule->AssetClassPaths.Contains(TEXT("/Script/CoreUObject.ScriptStruct")));
			TestTrue(TEXT("Allows F prefix"), Rule->AllowedPrefixes.Contains(TEXT("F")));
			TestTrue(TEXT("Allows S prefix"), Rule->AllowedPrefixes.Contains(TEXT("S")));
		});
	});

	Describe("Blueprint specialty rules", [this]()
	{
		It("Blueprint Interface rule is configured with expected class/prefix", [this]()
		{
			const UUE5StyleGuideRule_AssetNaming_BlueprintInterface* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_BlueprintInterface>(GetTransientPackage());
			TestNotNull(TEXT("Rule object created"), Rule);
			if (!Rule)
			{
				return;
			}

			TestTrue(TEXT("Uses Blueprint class path"), Rule->AssetClassPaths.Contains(TEXT("/Script/Engine.Blueprint")));
			TestEqual(TEXT("Prefix is BPI_"), Rule->Prefix, FString(TEXT("BPI_")));
		});

		It("Blueprint Macro Library rule is configured with expected class/prefix", [this]()
		{
			const UUE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary>(GetTransientPackage());
			TestNotNull(TEXT("Rule object created"), Rule);
			if (!Rule)
			{
				return;
			}

			TestTrue(TEXT("Uses Blueprint class path"), Rule->AssetClassPaths.Contains(TEXT("/Script/Engine.Blueprint")));
			TestEqual(TEXT("Prefix is BPML_"), Rule->Prefix, FString(TEXT("BPML_")));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS

