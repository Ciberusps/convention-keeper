// Pavel Penkov 2025 All Rights Reserved.

#include "Misc/AutomationTest.h"
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
}

#endif // WITH_DEV_AUTOMATION_TESTS
