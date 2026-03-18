// Pavel Penkov 2025 All Rights Reserved.

#include "Commandlets/ConventionKeeperCommandlet.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(ConventionKeeperCommandletSpec,
	"ConventionKeeper.Commandlet",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(ConventionKeeperCommandletSpec)

void ConventionKeeperCommandletSpec::Define()
{
	Describe("ConvertPathToRelativeForExclusion", [this]()
	{
		It("returns path without trailing slash for asset path when bFolder is false (add specific file to exclusions)", [this]()
		{
			const FString AssetPath = TEXT("/Game/GameCode/Characters/Player/MyAsset");
			FString Result = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(AssetPath, false);
			TestFalse(TEXT("Asset path must not end with slash"), Result.EndsWith(TEXT("/")));
			TestTrue(TEXT("Result must be in Content form"), Result.StartsWith(TEXT("Content/")));
		});

		It("returns path with trailing slash for folder when bFolder is true", [this]()
		{
			const FString FolderPath = TEXT("/Game/GameCode/Characters/Player");
			FString Result = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(FolderPath, true);
			TestTrue(TEXT("Folder path must end with slash"), Result.EndsWith(TEXT("/")));
			TestTrue(TEXT("Result must be in Content form"), Result.StartsWith(TEXT("Content/")));
		});

		It("normalizes object path /Game/.../Asset.Asset to package path without object suffix", [this]()
		{
			const FString ObjectPath = TEXT("/Game/GameCode/Textures/Decals/Ffsdafkl.Ffsdafkl");
			FString Result = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(ObjectPath, false);
			TestEqual(TEXT("Object path normalized to package path"), Result,
				FString(TEXT("Content/GameCode/Textures/Decals/Ffsdafkl")));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
