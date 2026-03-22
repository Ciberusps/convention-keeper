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

	Describe("PruneAncestorContentFolderPaths", [this]()
	{
		It("leaves empty array empty", [this]()
		{
			TArray<FString> Paths;
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 0);
		});

		It("keeps a single path unchanged", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/GameCode/Characters/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 1);
			TestEqual(TEXT("Path"), Paths[0], FString(TEXT("Content/GameCode/Characters/")));
		});

		It("drops strict ancestor when descendant is in the list", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/GameCode/"));
			Paths.Add(TEXT("Content/GameCode/NewFolder/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 1);
			TestEqual(TEXT("Keeps deepest"), Paths[0], FString(TEXT("Content/GameCode/NewFolder/")));
		});

		It("keeps only deepest of three levels", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/GameCode/"));
			Paths.Add(TEXT("Content/GameCode/Sub/"));
			Paths.Add(TEXT("Content/GameCode/Sub/Leaf/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 1);
			TestEqual(TEXT("Leaf"), Paths[0], FString(TEXT("Content/GameCode/Sub/Leaf/")));
		});

		It("keeps both siblings under same parent", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/GameCode/A/"));
			Paths.Add(TEXT("Content/GameCode/B/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 2);
		});

		It("does not treat Content/Game/ as ancestor of Content/GameDev/ (path boundary)", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/Game/"));
			Paths.Add(TEXT("Content/GameDev/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 2);
		});

		It("does not treat Content/A/ as ancestor of Content/AB/", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/A/"));
			Paths.Add(TEXT("Content/AB/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 2);
		});

		It("deduplicates identical paths", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT("Content/GameCode/X/"));
			Paths.Add(TEXT("Content/GameCode/X/"));
			Paths.Add(TEXT("Content/GameCode/X/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 1);
		});

		It("removes empty entries then prunes ancestors", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT(""));
			Paths.Add(TEXT("Content/GameCode/"));
			Paths.Add(TEXT("Content/GameCode/Nested/"));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 1);
			TestEqual(TEXT("Nested"), Paths[0], FString(TEXT("Content/GameCode/Nested/")));
		});

		It("only empty strings yields empty array", [this]()
		{
			TArray<FString> Paths;
			Paths.Add(TEXT(""));
			Paths.Add(TEXT(""));
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Paths);
			TestEqual(TEXT("Num"), Paths.Num(), 0);
		});
	});

	Describe("Folder batch: ConvertPathToRelativeForValidation then prune", [this]()
	{
		auto ConvertAndPruneGameFolderPaths = [](TArray<FString> GamePaths) -> TArray<FString>
		{
			TArray<FString> Relative;
			Relative.Reserve(GamePaths.Num());
			for (const FString& P : GamePaths)
			{
				Relative.Add(UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(P));
			}
			Relative.RemoveAll([](const FString& S) { return S.IsEmpty(); });
			UConventionKeeperCommandlet::PruneAncestorContentFolderPaths(Relative);
			return Relative;
		};

		It("parent and child /Game paths collapse to deepest Content folder", [this, ConvertAndPruneGameFolderPaths]()
		{
			TArray<FString> GamePaths;
			GamePaths.Add(TEXT("/Game/GameCode/"));
			GamePaths.Add(TEXT("/Game/GameCode/NewFolder/"));
			TArray<FString> Result = ConvertAndPruneGameFolderPaths(GamePaths);
			TestEqual(TEXT("Num"), Result.Num(), 1);
			TestTrue(TEXT("Content form with slash"), Result[0].StartsWith(TEXT("Content/")));
			TestTrue(TEXT("ends with slash"), Result[0].EndsWith(TEXT("/")));
			TestTrue(TEXT("contains NewFolder"), Result[0].Contains(TEXT("NewFolder")));
		});

		It("single /Game folder survives pipeline", [this, ConvertAndPruneGameFolderPaths]()
		{
			TArray<FString> GamePaths;
			GamePaths.Add(TEXT("/Game/GameCode/OnlyOne/"));
			TArray<FString> Result = ConvertAndPruneGameFolderPaths(GamePaths);
			TestEqual(TEXT("Num"), Result.Num(), 1);
			TestEqual(
				TEXT("Path"),
				Result[0],
				FString(TEXT("Content/GameCode/OnlyOne/")));
		});

		It("pipeline keeps siblings after conversion", [this, ConvertAndPruneGameFolderPaths]()
		{
			TArray<FString> GamePaths;
			GamePaths.Add(TEXT("/Game/Proj/Foo/"));
			GamePaths.Add(TEXT("/Game/Proj/Bar/"));
			TArray<FString> Result = ConvertAndPruneGameFolderPaths(GamePaths);
			TestEqual(TEXT("Num"), Result.Num(), 2);
		});
	});

	Describe("GetParentGameFolderPackagePathForValidationQueue", [this]()
	{
		It("returns parent with trailing slash for nested folder path", [this]()
		{
			const FString Parent = UConventionKeeperCommandlet::GetParentGameFolderPackagePathForValidationQueue(
				FString(TEXT("/Game/GameCode/Inventory/fqwef")));
			TestEqual(TEXT("Parent"), Parent, FString(TEXT("/Game/GameCode/Inventory/")));
		});

		It("accepts Game/ prefix without leading slash", [this]()
		{
			const FString Parent = UConventionKeeperCommandlet::GetParentGameFolderPackagePathForValidationQueue(
				FString(TEXT("Game/GameCode/Inventory/Second")));
			TestEqual(TEXT("Parent"), Parent, FString(TEXT("/Game/GameCode/Inventory/")));
		});

		It("returns empty when parent would be content root only", [this]()
		{
			const FString Parent =
				UConventionKeeperCommandlet::GetParentGameFolderPackagePathForValidationQueue(FString(TEXT("/Game/GameCode")));
			TestTrue(TEXT("empty for /Game/ parent"), Parent.IsEmpty());
		});

		It("strips object path suffix before resolving parent", [this]()
		{
			const FString Parent = UConventionKeeperCommandlet::GetParentGameFolderPackagePathForValidationQueue(
				FString(TEXT("/Game/GameCode/Tex/MyTex.MyTex")));
			TestEqual(TEXT("Parent"), Parent, FString(TEXT("/Game/GameCode/Tex/")));
		});
	});

}

#endif // WITH_DEV_AUTOMATION_TESTS
