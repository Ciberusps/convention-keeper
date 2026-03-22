// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperEditor.h"
#include "ConventionCoverage.h"
#include "ConventionKeeperEditorStyle.h"
#include "ConventionKeeperEditorCommands.h"
#include "Commandlets/ConventionKeeperCommandlet.h"
#include "ConventionKeeperConvention_Base.h"
#include "Development/ConventionKeeperSettings.h"
#include "Development/ConventionKeeperSettingsCustomization.h"
#include "Development/ConventionKeeperConventionDetailCustomization.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "PropertyEditorModule.h"
#include "Rules/ConventionKeeperRule.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions/ConventionAssetTypeActions.h"
#include "ContentBrowserModule.h"
#include "ContentBrowserDelegates.h"
#include "Developer/MessageLog/Public/MessageLogModule.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Logging/MessageLog.h"
#include "MessageLogInitializationOptions.h"
#include "Misc/MessageDialog.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"
#include "UObject/ObjectSaveContext.h"
#include "UObject/Package.h"

#if WITH_EDITOR
#include "Editor.h"
#include "TimerManager.h"
#endif

DEFINE_LOG_CATEGORY(LogConventionKeeper);

static const FName ConventionKeeperEditorTabName("ConventionKeeperEditor");

#define LOCTEXT_NAMESPACE "FConventionKeeperEditorModule"

void FConventionKeeperEditorModule::StartupModule()
{
	UE_LOG(LogConventionKeeper, Log, TEXT(">>> ConventionKeeperEditor StartupModule() called"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FConventionKeeperEditorStyle::Initialize();
	FConventionKeeperEditorStyle::ReloadTextures();

	FConventionKeeperEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FConventionKeeperEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FConventionKeeperEditorModule::PluginButtonClicked),
		FCanExecuteAction());
	PluginCommands->MapAction(
		FConventionKeeperEditorCommands::Get().CoverageAction,
		FExecuteAction::CreateRaw(this, &FConventionKeeperEditorModule::RunCoverageTest),
		FCanExecuteAction());
	PluginCommands->MapAction(
		FConventionKeeperEditorCommands::Get().ComplianceAction,
		FExecuteAction::CreateRaw(this, &FConventionKeeperEditorModule::RunComplianceTest),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FConventionKeeperEditorModule::RegisterMenus));

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	FMessageLogInitializationOptions InitOptions;
	InitOptions.bShowFilters = true;
	MessageLogModule.RegisterLogListing("ConventionKeeper", LOCTEXT("ConventionKeeperLogLabel", "Convention Keeper"), InitOptions);

	// *Also* immediately inject & refresh so you don’t depend on the callback timing:
	RegisterMenus();
	UToolMenus::Get()->RefreshAllWidgets();
	RegisterAssetTypeActions();
	RegisterContentBrowserExtenders();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(
		UConventionKeeperSettings::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FConventionKeeperSettingsCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(
		UConventionKeeperConvention_Base::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FConventionKeeperConventionDetailCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();

#if WITH_EDITOR
	PackageSavedDelegateHandle = UPackage::PackageSavedWithContextEvent.AddLambda(
		[this](const FString& FileName, UPackage* Pkg, const FObjectPostSaveContext& Ctx) { OnPackageSaved(FileName, Pkg, Ctx); });
#endif
}

void FConventionKeeperEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FConventionKeeperEditorStyle::Shutdown();
	FConventionKeeperEditorCommands::Unregister();

	UnregisterAssetTypeActions();
	UnregisterContentBrowserExtenders();

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(UConventionKeeperSettings::StaticClass()->GetFName());
		PropertyModule.UnregisterCustomClassLayout(UConventionKeeperConvention_Base::StaticClass()->GetFName());
	}

#if WITH_EDITOR
	if (PackageSavedDelegateHandle.IsValid())
	{
		UPackage::PackageSavedWithContextEvent.Remove(PackageSavedDelegateHandle);
		PackageSavedDelegateHandle.Reset();
	}
#endif
}

void FConventionKeeperEditorModule::PluginButtonClicked()
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	if (!ConventionKeeperSettings)
	{
		FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoSettings", "Convention Keeper: Project Settings not found."));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
		return;
	}

	if (!ConventionKeeperSettings->GetEffectiveValidationEnabled())
	{
		FMessageLog(TEXT("ConventionKeeper")).Info(ConventionKeeperLoc::GetText(FName(TEXT("ValidationDisabled"))));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Info, true);
		return;
	}

	UConventionKeeperConvention_Base* Convention = ConventionKeeperSettings->GetResolvedConvention();
	if (!Convention)
	{
		FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoConvention", "Convention Keeper: Convention is not set. Set Convention or Convention Asset in Project Settings → Convention Keeper."));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
		return;
	}

	UConventionKeeperCommandlet::ValidateData(TArrayView<const FString>(), false);
}

void FConventionKeeperEditorModule::RunCoverageTest()
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings)
	{
		FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoSettings", "Convention Keeper: Project Settings not found."));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
		return;
	}

	UConventionKeeperConvention_Base* Convention = Settings->GetResolvedConvention();
	if (!Convention)
	{
		FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoConvention", "Convention Keeper: Convention is not set. Set Convention or Convention Asset in Project Settings → Convention Keeper."));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
		return;
	}

	FConventionCoverageResult Result = ConventionCoverage::RunAnalysis(Convention, Settings, TArray<FString>());
	ConventionCoverage::ReportToMessageLog(Result, ConventionCoverage::EConventionReportMode::CoverageOnly, true);
}

void FConventionKeeperEditorModule::RunComplianceTest()
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings)
	{
		FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoSettings", "Convention Keeper: Project Settings not found."));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
		return;
	}

	UConventionKeeperConvention_Base* Convention = Settings->GetResolvedConvention();
	if (!Convention)
	{
		FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoConvention", "Convention Keeper: Convention is not set. Set Convention or Convention Asset in Project Settings → Convention Keeper."));
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
		return;
	}

	FConventionCoverageResult Result = ConventionCoverage::RunAnalysis(Convention, Settings, TArray<FString>());
	ConventionCoverage::ReportToMessageLog(Result, ConventionCoverage::EConventionReportMode::ComplianceOnly, true);
}

bool FConventionKeeperEditorModule::CheckAssetPathExists(const FString& PackagePath)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.PackagePaths.Add(*PackagePath);
	Filter.bRecursivePaths = false; // or true if you want subfolders too

	TArray<FAssetData> AssetData;
	AssetRegistry.GetAssets(Filter, AssetData);

	if (AssetData.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Assets found in: %s"), *PackagePath);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No assets found in: %s"), *PackagePath);
		return false;
	}
}

void FConventionKeeperEditorModule::RegisterMenus()
{
	UE_LOG(LogConventionKeeper, Log, TEXT(">>> ConventionKeeperEditor::RegisterMenus() called"));

	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
	if (Menu)
	{
		FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
		Section.AddMenuEntryWithCommandList(FConventionKeeperEditorCommands::Get().PluginAction, PluginCommands);
		Section.AddMenuEntryWithCommandList(FConventionKeeperEditorCommands::Get().CoverageAction, PluginCommands);
		Section.AddMenuEntryWithCommandList(FConventionKeeperEditorCommands::Get().ComplianceAction, PluginCommands);
	}

	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	if (!ToolbarMenu)
	{
		return;
	}

	FToolMenuSection& Section = ToolbarMenu->AddSection(
		"ConventionKeeperExtensions",
		TAttribute<FText>(),
		FToolMenuInsert("Play", EToolMenuInsertType::Default)
	);

	FToolMenuEntry Entry = FToolMenuEntry::InitToolBarButton(FConventionKeeperEditorCommands::Get().PluginAction);
	Entry.SetCommandList(PluginCommands);
	Entry.Label = LOCTEXT("ConventionKeeperToolbarLabel", "ConventionKeeper");
	Entry.ToolTip = LOCTEXT("ConventionKeeperToolbarTooltip", "Validate convention folders");
	Entry.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Tools");
	Entry.StyleNameOverride = "CalloutToolbar";

	Section.AddEntry(Entry);
}

void FConventionKeeperEditorModule::RegisterAssetTypeActions()
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsModule.Get();

	TSharedRef<IAssetTypeActions> ConventionActions = MakeShareable(new FConventionTypeActions());
	AssetTools.RegisterAssetTypeActions(ConventionActions);
	RegisteredAssetTypeActions.Add(ConventionActions);
}

void FConventionKeeperEditorModule::UnregisterAssetTypeActions()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		RegisteredAssetTypeActions.Empty();
		return;
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsModule.Get();

	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredAssetTypeActions)
	{
		if (Action.IsValid())
		{
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}

	RegisteredAssetTypeActions.Empty();
}

static void ValidateConventionFolders(const TArray<FString> SelectedPaths)
{
	TArray<FString> Normalized;
	Normalized.Reserve(SelectedPaths.Num());
	for (const FString& P : SelectedPaths)
	{
		FString S = P;
		S.ReplaceInline(TEXT("\\"), TEXT("/"));
		S.TrimStartAndEndInline();
		if (!S.IsEmpty() && !S.EndsWith(TEXT("/")))
		{
			S += TEXT("/");
		}
		Normalized.Add(S);
	}
	UConventionKeeperCommandlet::ValidateData(MakeArrayView(Normalized), false);
}

static void ValidateConventionAssets(const TArray<FString> AssetPaths)
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	TArray<FString> Filtered;
	for (const FString& Path : AssetPaths)
	{
		FString Normalized = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(Path, false);
		if (!Normalized.IsEmpty() && (!Settings || !Settings->Exclusions.Contains(Normalized)))
		{
			Filtered.Add(Path);
		}
	}
	if (Filtered.Num() > 0)
	{
		UConventionKeeperCommandlet::ValidateData(MakeArrayView(Filtered), true);
	}
}

static void AddToExclusionsWithConfirmation(const TArray<FString>& Paths, bool bFolder)
{
	if (Paths.IsEmpty()) return;
	if (FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("ConfirmAddToExclusion", "Are you SURE you want to add to exclusions?")) != EAppReturnType::Yes)
	{
		return;
	}
	UConventionKeeperSettings* Settings = GetMutableDefault<UConventionKeeperSettings>();
	if (!Settings) return;
	for (const FString& Path : Paths)
	{
		FString Normalized = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(Path, bFolder);
		if (Normalized.IsEmpty()) continue;
		if (!Settings->Exclusions.Contains(Normalized))
		{
			Settings->Exclusions.Add(Normalized);
		}
	}
	Settings->SaveConfig();
}

static void CreateConventionFolderMenu(FMenuBuilder& MenuBuilder, const TArray<FString> SelectedPaths)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("ConventionKeeperValidateFolderTitle", "Validate Convention In Folder"),
		LOCTEXT("ConventionKeeperValidateFolderTooltip", "Run convention validation on the selected folder(s)."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Tools"),
		FUIAction(FExecuteAction::CreateStatic(ValidateConventionFolders, SelectedPaths))
	);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("ConventionKeeperAddToExclusionTitle", "ConventionKeeper add to Exclusion"),
		LOCTEXT("ConventionKeeperAddToExclusionTooltip", "Add the selected folder(s) to Convention Keeper exclusions."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Tools"),
		FUIAction(FExecuteAction::CreateLambda([SelectedPaths]() { AddToExclusionsWithConfirmation(SelectedPaths, true); }))
	);
}

static TSharedRef<FExtender> OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> Extender(new FExtender());
	Extender->AddMenuExtension(
		"PathContextBulkOperations",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(CreateConventionFolderMenu, SelectedPaths)
	);
	return Extender;
}

static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets)
{
	TArray<FString> AssetPathsForValidate;
	TArray<FString> AssetPathsForExclusion;
	for (const FAssetData& Asset : SelectedAssets)
	{
		FString PackageName = Asset.PackageName.ToString();
		if (!PackageName.IsEmpty())
		{
			AssetPathsForValidate.AddUnique(PackageName);
			AssetPathsForExclusion.AddUnique(PackageName);
		}
	}
	TSharedRef<FExtender> Extender(new FExtender());
	Extender->AddMenuExtension(
		"GetAssetActions",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateLambda([AssetPathsForValidate, AssetPathsForExclusion](FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddMenuEntry(
				LOCTEXT("ConventionKeeperValidateAssetTitle", "Validate Convention"),
				LOCTEXT("ConventionKeeperValidateAssetTooltip", "Run convention validation for the selected asset(s) only. Excluded assets are skipped."),
				FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Tools"),
				FUIAction(FExecuteAction::CreateLambda([AssetPathsForValidate]() { ValidateConventionAssets(AssetPathsForValidate); }))
			);
			MenuBuilder.AddMenuEntry(
				LOCTEXT("ConventionKeeperAddToExclusionAssetTitle", "ConventionKeeper add to Exclusion"),
				LOCTEXT("ConventionKeeperAddToExclusionTooltip", "Add the selected asset(s) to Convention Keeper exclusions."),
				FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Tools"),
				FUIAction(FExecuteAction::CreateLambda([AssetPathsForExclusion]() { AddToExclusionsWithConfirmation(AssetPathsForExclusion, false); }))
			);
		})
	);
	return Extender;
}

void FConventionKeeperEditorModule::RegisterContentBrowserExtenders()
{
	if (!FSlateApplication::IsInitialized())
	{
		return;
	}

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	auto& PathMenuExtenders = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	PathMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateStatic(OnExtendContentBrowserPathSelectionMenu));
	ContentBrowserPathExtenderDelegateHandle = PathMenuExtenders.Last().GetHandle();

	auto& AssetMenuExtenders = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	AssetMenuExtenders.Add(FContentBrowserMenuExtender_SelectedAssets::CreateStatic(OnExtendContentBrowserAssetSelectionMenu));
	ContentBrowserAssetExtenderDelegateHandle = AssetMenuExtenders.Last().GetHandle();
}

void FConventionKeeperEditorModule::UnregisterContentBrowserExtenders()
{
	if (FContentBrowserModule* ContentBrowserModule = FModuleManager::GetModulePtr<FContentBrowserModule>(TEXT("ContentBrowser")))
	{
		auto& PathMenuExtenders = ContentBrowserModule->GetAllPathViewContextMenuExtenders();
		PathMenuExtenders.RemoveAll(
			[&Handle = ContentBrowserPathExtenderDelegateHandle](const FContentBrowserMenuExtender_SelectedPaths& Delegate)
			{
				return Delegate.GetHandle() == Handle;
			}
		);
		auto& AssetMenuExtenders = ContentBrowserModule->GetAllAssetViewContextMenuExtenders();
		AssetMenuExtenders.RemoveAll(
			[&Handle = ContentBrowserAssetExtenderDelegateHandle](const FContentBrowserMenuExtender_SelectedAssets& Delegate)
			{
				return Delegate.GetHandle() == Handle;
			}
		);
	}
}

#if WITH_EDITOR
void FConventionKeeperEditorModule::OnPackageSaved(const FString& PackageFileName, UPackage* Package, const FObjectPostSaveContext& SaveContext)
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings || !Settings->GetEffectiveValidationEnabled() || !Settings->bValidateAssetNamingOnSave || !Package)
	{
		return;
	}
	if (GEditor && GEditor->IsAutosaving())
	{
		return;
	}
	FString PackagePath = Package->GetPathName();
	if (PackagePath.IsEmpty() || !PackagePath.StartsWith(TEXT("/Game/")))
	{
		return;
	}
	SavedPackagePathsToValidate.AddUnique(PackagePath);
	GEditor->GetTimerManager()->SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() { ValidateSavedPackages(); }));
}

void FConventionKeeperEditorModule::ValidateSavedPackages()
{
	if (SavedPackagePathsToValidate.Num() == 0)
	{
		return;
	}
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings || !Settings->GetEffectiveValidationEnabled())
	{
		SavedPackagePathsToValidate.Empty();
		return;
	}
	UConventionKeeperConvention_Base* Convention = Settings->GetResolvedConvention();
	if (!Convention)
	{
		SavedPackagePathsToValidate.Empty();
		return;
	}
	TArray<FString> PathsToValidate;
	for (const FString& PackagePath : SavedPackagePathsToValidate)
	{
		FString Relative = UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(PackagePath, false);
		if (Relative.IsEmpty())
		{
			continue;
		}
		if (Settings->Exclusions.Contains(Relative))
		{
			continue;
		}
		PathsToValidate.Add(PackagePath);
	}
	SavedPackagePathsToValidate.Empty();
	if (PathsToValidate.Num() > 0)
	{
		UConventionKeeperCommandlet::ValidateData(PathsToValidate, true);
	}
}
#endif

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FConventionKeeperEditorModule, ConventionKeeperEditor)
