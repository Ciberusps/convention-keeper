// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_AssetValidation.h"

#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Editor.h"
#include "Engine/Level.h"
#include "Misc/DataValidation.h"
#include "Misc/PackageName.h"
#include "Rules/ConventionKeeperRule_FolderStructure.h"
#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "ConventionKeeperValidationContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_AssetValidation)

#define LOCTEXT_NAMESPACE "ConventionKeeperRule_AssetValidation"

static void LogIssuesFromDataValidationContext(
	const UConventionKeeperRule* Rule,
	EMessageSeverity::Type FailureSeverity,
	const FString& ContentPathForLink,
	const FDataValidationContext& Context)
{
	const FString* const LinkPtr = ContentPathForLink.IsEmpty() ? nullptr : &ContentPathForLink;
	for (const FDataValidationContext::FIssue& Issue : Context.GetIssues())
	{
		const EMessageSeverity::Type Sev =
			(Issue.Severity == EMessageSeverity::Error) ? FailureSeverity : EMessageSeverity::Warning;
		UConventionKeeperRule::LogRuleMessage(Rule, Sev, Issue.Message, LinkPtr);
	}
}

namespace AssetValidationRulePath
{
static FString SelectedPathAsContentFolderForm(const FString& InPath)
{
	FString Path = InPath;
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));
	Path.TrimStartAndEndInline();
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
	if (Path.StartsWith(TEXT("Game/")))
	{
		Path = FString(TEXT("Content/")) + Path.Mid(5);
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
	if (!Path.EndsWith(TEXT("/")))
	{
		Path += TEXT("/");
	}
	return Path;
}

static FString PackageNameToContentFolderWithSlash(const FString& LongPackageName)
{
	if (!LongPackageName.StartsWith(TEXT("/Game/")))
	{
		return FString();
	}
	return FString(TEXT("Content/")) + LongPackageName.Mid(6) + TEXT("/");
}

static bool RootOverlapsSelected(const FString& RootNormWithSlash, const FString& SelectedRaw)
{
	const FString SelNorm = SelectedPathAsContentFolderForm(SelectedRaw);
	return SelNorm.StartsWith(RootNormWithSlash) || RootNormWithSlash.StartsWith(SelNorm);
}

static TArray<FString> ResolveValidationRoots(
	const FString& RootPathProperty,
	const TMap<FString, FString>& Placeholders,
	const UConventionKeeperSettings* Settings)
{
	TArray<FString> Out;
	const FString Resolved = UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(RootPathProperty, Placeholders);

	if (Resolved.Contains(TEXT("{")))
	{
		TMap<FString, FString> PlaceholdersWithBraces = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();
		for (const TTuple<FString, FString>& P : Placeholders)
		{
			FString Key = P.Key;
			if (!Key.StartsWith(TEXT("{")))
			{
				Key = FString::Printf(TEXT("{%s}"), *P.Key);
			}
			PlaceholdersWithBraces.Add(Key, P.Value);
		}
		TArray<FString> ResolvedList = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(Resolved, PlaceholdersWithBraces);
		for (FString& P : ResolvedList)
		{
			P.ReplaceInline(TEXT("\\"), TEXT("/"));
			if (P.StartsWith(TEXT("/")))
			{
				P.RemoveFromStart(TEXT("/"));
			}
			if (!P.IsEmpty() && !P.Contains(TEXT("{")))
			{
				Out.Add(UConventionKeeperRule::NormalizeRelativePath(P));
			}
		}
		if (Out.IsEmpty())
		{
			FString Fallback = Resolved;
			Fallback.ReplaceInline(TEXT("\\"), TEXT("/"));
			Fallback.TrimStartAndEndInline();
			while (Fallback.StartsWith(TEXT("/")))
			{
				Fallback.RemoveFromStart(TEXT("/"));
			}
			if (!Fallback.IsEmpty() && !Fallback.Contains(TEXT("{")))
			{
				Out.Add(UConventionKeeperRule::NormalizeRelativePath(Fallback));
			}
		}
	}
	else
	{
		Out.Add(UConventionKeeperRule::NormalizeRelativePath(Resolved));
	}
	return Out;
}

}

bool UConventionKeeperRule_AssetValidation::CanValidate_Implementation(
	const TArray<FString>& SelectedPaths,
	const TMap<FString, FString>& Placeholders) const
{
#if !WITH_EDITOR
	return false;
#else
	if (!GEditor)
	{
		return false;
	}
	if (!bValidateOnPerAssetSave && FConventionKeeperAssetValidationScope::IsPerAssetPackageValidation())
	{
		return false;
	}
	if (!EditorValidatorClass || EditorValidatorClass->HasAnyClassFlags(CLASS_Abstract))
	{
		return false;
	}
	if (ValidationRoot.Path.IsEmpty())
	{
		return false;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const TArray<FString> Roots = AssetValidationRulePath::ResolveValidationRoots(ValidationRoot.Path, Placeholders, Settings);
	if (Roots.IsEmpty())
	{
		return false;
	}

	for (const FString& RootNorm : Roots)
	{
		if (Settings && UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(RootNorm, Settings->Exclusions, Placeholders))
		{
			continue;
		}

		if (SelectedPaths.IsEmpty())
		{
			return true;
		}

		for (const FString& Sel : SelectedPaths)
		{
			if (AssetValidationRulePath::RootOverlapsSelected(RootNorm, Sel))
			{
				return true;
			}
		}
	}
	return false;
#endif
}

void UConventionKeeperRule_AssetValidation::Validate_Implementation(
	const TArray<FString>& SelectedPaths,
	const TMap<FString, FString>& Placeholders)
{
#if !WITH_EDITOR
	return;
#else
	if (!CanValidate(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const EMessageSeverity::Type FailureSev = ConventionKeeperRuleSeverityToMessageSeverity(Severity);

	const TArray<FString> Roots = AssetValidationRulePath::ResolveValidationRoots(ValidationRoot.Path, Placeholders, Settings);
	if (Roots.IsEmpty())
	{
		return;
	}

	UClass* ValidatorClass = EditorValidatorClass.Get();
	if (!ValidatorClass || ValidatorClass->HasAnyClassFlags(CLASS_Abstract))
	{
		return;
	}

	UEditorValidatorBase* Validator = NewObject<UEditorValidatorBase>(GetTransientPackage(), ValidatorClass);
	if (!Validator || !Validator->IsEnabled())
	{
		return;
	}

	FAssetRegistryModule& RegModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = RegModule.Get();

	FARFilter Filter;
	Filter.bRecursivePaths = bRecursive;
	Filter.bIncludeOnlyOnDiskAssets = false;

	for (const FString& RootNorm : Roots)
	{
		if (Settings && UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(RootNorm, Settings->Exclusions, Placeholders))
		{
			continue;
		}

		FString RootNoSlash = RootNorm;
		while (RootNoSlash.EndsWith(TEXT("/")))
		{
			RootNoSlash.LeftChopInline(1);
		}
		if (!RootNoSlash.StartsWith(TEXT("Content/")))
		{
			continue;
		}
		const FString LongPkg = FString(TEXT("/Game/")) + RootNoSlash.Mid(8);
		if (!FPackageName::IsValidLongPackageName(LongPkg))
		{
			continue;
		}
		Filter.PackagePaths.Add(FName(*LongPkg));
	}

	if (Filter.PackagePaths.IsEmpty())
	{
		return;
	}

	TArray<FAssetData> Assets;
	AssetRegistry.GetAssets(Filter, Assets);

	const bool bFilterBySelection = SelectedPaths.Num() > 0;

	for (const FAssetData& AssetData : Assets)
	{
		if (!AssetData.IsValid())
		{
			continue;
		}

		const FString AssetFolder = AssetValidationRulePath::PackageNameToContentFolderWithSlash(AssetData.PackageName.ToString());
		if (AssetFolder.IsEmpty())
		{
			continue;
		}

		if (Settings)
		{
			const FString ExclTest = AssetFolder;
			FString ExclPath = ExclTest;
			while (ExclPath.EndsWith(TEXT("/")))
			{
				ExclPath.LeftChopInline(1);
			}
			if (UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(ExclPath + TEXT("/"), Settings->Exclusions, Placeholders))
			{
				continue;
			}
		}

		if (bFilterBySelection)
		{
			bool bKeep = false;
			for (const FString& Sel : SelectedPaths)
			{
				const FString SelNorm = AssetValidationRulePath::SelectedPathAsContentFolderForm(Sel);
				if (AssetFolder.StartsWith(SelNorm))
				{
					bKeep = true;
					break;
				}
			}
			if (!bKeep)
			{
				continue;
			}
		}

		UObject* Obj = AssetData.GetAsset({ ULevel::LoadAllExternalObjectsTag });
		FString ContentPathForLink;
		if (AssetData.PackageName.ToString().StartsWith(TEXT("/Game/")))
		{
			ContentPathForLink = FString(TEXT("Content/")) + AssetData.PackageName.ToString().Mid(6);
		}
		if (!Obj)
		{
			UConventionKeeperRule::LogRuleMessage(
				this,
				FailureSev,
				LOCTEXT("LoadFailed", "Convention Keeper: failed to load asset for asset validation."),
				ContentPathForLink.IsEmpty() ? nullptr : &ContentPathForLink);
			continue;
		}

		if (LimitToAssetTypes.Num() > 0)
		{
			bool bTypeOk = false;
			for (const TSubclassOf<UObject>& TypeRoot : LimitToAssetTypes)
			{
				if (TypeRoot && Obj->IsA(TypeRoot))
				{
					bTypeOk = true;
					break;
				}
			}
			if (!bTypeOk)
			{
				continue;
			}
		}

		FDataValidationContext Context(
			/*InWasAssetLoadedForValidation=*/true,
			EDataValidationUsecase::Manual,
			/*InAssociatedObjects=*/{});

		if (bRunClassIsDataValid)
		{
			const EDataValidationResult ClassResult = static_cast<const UObject*>(Obj)->IsDataValid(Context);
			if (ClassResult == EDataValidationResult::Invalid)
			{
				LogIssuesFromDataValidationContext(this, FailureSev, ContentPathForLink, Context);
				continue;
			}
		}

		Validator->ValidateLoadedAsset(AssetData, Obj, Context);
		LogIssuesFromDataValidationContext(this, FailureSev, ContentPathForLink, Context);
	}
#endif
}

#undef LOCTEXT_NAMESPACE
