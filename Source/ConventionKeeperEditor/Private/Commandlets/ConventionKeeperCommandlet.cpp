// Pavel Penkov 2025 All Rights Reserved.

#include "Commandlets/ConventionKeeperCommandlet.h"
#include "Development/ConventionKeeperSettings.h"
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
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}

static FString ConvertPathToRelativeForValidation(const FString& InPath)
{
	if (InPath.StartsWith(TEXT("Content/")) || InPath.StartsWith(TEXT("/Content/")))
	{
		return NormalizeRelativePathForValidation(InPath);
	}

	if (FPackageName::IsValidLongPackageName(InPath))
	{
		FString Filename = FPackageName::LongPackageNameToFilename(InPath, TEXT(""));
		FPaths::MakePathRelativeTo(Filename, *FPaths::ProjectDir());
		return NormalizeRelativePathForValidation(Filename);
	}

	FString Result = InPath;
	Result.RemoveFromStart(TEXT("/Game"));
	Result.RemoveFromStart(TEXT("Game"));
	Result = FString::Printf(TEXT("Content/%s"), *Result);
	return NormalizeRelativePathForValidation(Result);
}

bool UConventionKeeperCommandlet::ValidateData(TArrayView<const FString> Paths)
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	if (!ConventionKeeperSettings || !ConventionKeeperSettings->Convention.Get())
	{
		UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Settings or Convention class is not set."));
		return false;
	}

	UConvention* Convention = ConventionKeeperSettings->Convention.GetDefaultObject();
	if (!Convention)
	{
		UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Failed to get Convention default object."));
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
		RelativePaths.Add(ConvertPathToRelativeForValidation(Path));
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
