// Pavel Penkov 2025 All Rights Reserved.

#include "Commandlets/ConventionKeeperCommandlet.h"
#include "Development/ConventionKeeperSettings.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Logging/MessageLog.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperCommandlet)

UConventionKeeperCommandlet::UConventionKeeperCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
	ShowErrorCount = true;
}

static FString NormalizeRelativePathForValidation(const FString& InPath)
{
	FString Result = InPath;
	Result.ReplaceInline(TEXT("\\"), TEXT("/"));
	Result.TrimStartAndEndInline();
	while (Result.StartsWith(TEXT("/")))
	{
		Result.RemoveFromStart(TEXT("/"));
	}
	if (Result.StartsWith(TEXT("All/")))
	{
		Result.RemoveFromStart(TEXT("All/"));
	}
	if (Result.StartsWith(TEXT("Game/")))
	{
		Result = FString(TEXT("Content/")) + Result.Mid(5);
	}
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}

FString UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(const FString& InPath)
{
	FString Path = InPath;
	Path.TrimStartAndEndInline();
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));

	const FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()).Replace(TEXT("\\"), TEXT("/"));
	if (Path.StartsWith(ProjectDir))
	{
		Path = Path.Mid(ProjectDir.Len());
	}
	else
	{
		const FString ContentMarker = TEXT("/Content/");
		const int32 ContentPos = Path.Find(ContentMarker);
		if (ContentPos != INDEX_NONE)
		{
			Path = FString(TEXT("Content/")) + Path.Mid(ContentPos + ContentMarker.Len());
		}
	}

	while (Path.StartsWith(TEXT("/")))
	{
		Path.RemoveFromStart(TEXT("/"));
	}
	if (Path.StartsWith(TEXT("All/")))
	{
		Path.RemoveFromStart(TEXT("All/"));
	}

	const int32 DotPos = Path.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (DotPos != INDEX_NONE)
	{
		const FString Ext = Path.Mid(DotPos + 1).ToLower();
		if (Ext == TEXT("uasset") || Ext == TEXT("umap"))
		{
			Path = Path.Left(DotPos);
		}
	}

	if (Path.StartsWith(TEXT("Content/")))
	{
		return NormalizeRelativePathForValidation(Path);
	}

	if (Path.StartsWith(TEXT("Game/")))
	{
		return NormalizeRelativePathForValidation(FString(TEXT("Content/")) + Path.Mid(5));
	}

	FString ForPackageName = Path;
	if (!ForPackageName.StartsWith(TEXT("Game")))
	{
		ForPackageName = FString(TEXT("Game/")) + ForPackageName;
	}
	if (FPackageName::IsValidLongPackageName(ForPackageName))
	{
		FString Filename = FPackageName::LongPackageNameToFilename(ForPackageName, TEXT(""));
		FPaths::MakePathRelativeTo(Filename, *FPaths::ProjectDir());
		return NormalizeRelativePathForValidation(Filename);
	}

	return NormalizeRelativePathForValidation(FString(TEXT("Content/")) + Path);
}

FString UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(const FString& InPath, bool bFolder)
{
	FString Result = ConvertPathToRelativeForValidation(InPath);
	if (!bFolder && Result.EndsWith(TEXT("/")))
	{
		Result.LeftChopInline(1);
	}
	return Result;
}

bool UConventionKeeperCommandlet::ValidateData(TArrayView<const FString> Paths, bool bAssetPaths)
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	if (ConventionKeeperSettings && !ConventionKeeperSettings->GetEffectiveValidationEnabled())
	{
		FText Msg = ConventionKeeperLoc::GetText(FName(TEXT("ValidationDisabled")));
		if (IsRunningCommandlet())
		{
			UE_LOG(LogTemp, Warning, TEXT("ConventionKeeper: %s"), *Msg.ToString());
		}
		else
		{
			FMessageLog(TEXT("ConventionKeeper")).Info(Msg);
			FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Info, true);
		}
		return true;
	}
	UConventionKeeperConvention_Base* Convention = ConventionKeeperSettings ? ConventionKeeperSettings->GetResolvedConvention() : nullptr;
	if (!Convention)
	{
		UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Settings or Convention/Convention Asset is not set."));
		return false;
	}

	if (Paths.IsEmpty())
	{
		Convention->ValidateFolderStructures();
		return true;
	}

	TArray<FString> RelativePaths;
	RelativePaths.Reserve(Paths.Num());
	for (const FString& Path : Paths)
	{
		RelativePaths.Add(bAssetPaths
			? UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(Path, false)
			: UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(Path));
	}

	Convention->ValidateFolderStructuresForPaths(RelativePaths);
	return true;
}

int32 UConventionKeeperCommandlet::Main(const FString& Params)
{
	TArray<FString> Paths;

	FString PathsValue;
	if (FParse::Value(*Params, TEXT("Paths="), PathsValue))
	{
		PathsValue.ParseIntoArray(Paths, TEXT(";"), true);
	}

	const bool bSuccess = ValidateData(Paths);
	return bSuccess ? 0 : 1;
}
