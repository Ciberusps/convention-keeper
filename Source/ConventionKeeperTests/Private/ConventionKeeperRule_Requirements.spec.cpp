// Pavel Penkov 2025 All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "Interfaces/IPluginManager.h"
#include "EarendilConvention/EarendilConvention.h"
#include "Rules/ConventionKeeperRule_NamingConvention_PascalCase.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionKeeperRule_RequirementsSpec,
	"ConventionKeeper.Rule.Requirements",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(ConventionKeeperRule_RequirementsSpec)

void ConventionKeeperRule_RequirementsSpec::Define()
{
	Describe("AreRequirementsSatisfied", [this]()
	{
		It("returns true when PluginRequirements is empty", [this]()
		{
			UConventionKeeperRule_NamingConvention_PascalCase* Rule = NewObject<UConventionKeeperRule_NamingConvention_PascalCase>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule)
			{
				return;
			}

			Rule->PluginRequirements.Empty();
			FString Reason;
			TestTrue(TEXT("No requirements should pass"), Rule->AreRequirementsSatisfied(&Reason));
			TestTrue(TEXT("Reason should be empty"), Reason.IsEmpty());
		});

		It("returns false when required plugin is missing", [this]()
		{
			UConventionKeeperRule_NamingConvention_PascalCase* Rule = NewObject<UConventionKeeperRule_NamingConvention_PascalCase>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule)
			{
				return;
			}

			Rule->PluginRequirements = { FName(TEXT("ConventionKeeper_NonExistent_Plugin_For_Test")) };
			Rule->bRequireAllPlugins = true;
			FString Reason;
			TestFalse(TEXT("Missing plugin should fail"), Rule->AreRequirementsSatisfied(&Reason));
			TestTrue(TEXT("Reason should mention missing"), Reason.Contains(TEXT("missing required plugin")));
		});

		It("returns true when at least one required plugin is enabled in any-mode", [this]()
		{
			UConventionKeeperRule_NamingConvention_PascalCase* Rule = NewObject<UConventionKeeperRule_NamingConvention_PascalCase>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule)
			{
				return;
			}

			TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();
			if (EnabledPlugins.Num() == 0)
			{
				AddWarning(TEXT("No enabled plugins found in environment; skipping any-mode positive check."));
				return;
			}

			Rule->PluginRequirements = {
				FName(TEXT("ConventionKeeper_NonExistent_Plugin_For_Test")),
				FName(*EnabledPlugins[0]->GetName())
			};
			Rule->bRequireAllPlugins = false;

			FString Reason;
			TestTrue(TEXT("Any-mode should pass when one plugin is enabled"), Rule->AreRequirementsSatisfied(&Reason));
		});
	});

	Describe("EarendilConvention StateTree rule requirements", [this]()
	{
		It("StateTree rule is filtered out from GetEffectiveRules when plugin requirement is unmet", [this]()
		{
			UEarendilConvention* Convention = NewObject<UEarendilConvention>(GetTransientPackage());
			TestNotNull(TEXT("Convention created"), Convention);
			if (!Convention)
			{
				return;
			}

			UConventionKeeperRule* StateTreeRule = nullptr;
			for (UConventionKeeperRule* Rule : Convention->Rules)
			{
				if (Rule && Rule->RuleId == FName(TEXT("ec-asset-naming-state-tree")))
				{
					StateTreeRule = Rule;
					break;
				}
			}
			TestNotNull(TEXT("Earendil StateTree rule exists in local Rules"), StateTreeRule);
			if (!StateTreeRule)
			{
				return;
			}

			StateTreeRule->PluginRequirements = { FName(TEXT("ConventionKeeper_NonExistent_Plugin_For_Test")) };
			StateTreeRule->bRequireAllPlugins = true;

			const TArray<UConventionKeeperRule*> EffectiveRules = Convention->GetEffectiveRules();
			bool bFound = false;
			for (UConventionKeeperRule* Rule : EffectiveRules)
			{
				if (Rule && Rule->RuleId == FName(TEXT("ec-asset-naming-state-tree")))
				{
					bFound = true;
					break;
				}
			}

			TestFalse(TEXT("Earendil StateTree rule should be skipped from effective rules"), bFound);
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
