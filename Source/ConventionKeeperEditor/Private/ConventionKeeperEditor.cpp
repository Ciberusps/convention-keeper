// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperEditor.h"
#include "ConventionKeeperEditorStyle.h"
#include "ConventionKeeperEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Developer/MessageLog/Public/MessageLogModule.h"
#include "Development/ConventionKeeperSettings.h"

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

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FConventionKeeperEditorModule::RegisterMenus));

	// Register the details customizer
	// FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	// PropertyModule.NotifyCustomizationModuleChanged();

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	MessageLogModule.RegisterLogListing("ConventionKeeper", FText::FromString("ConventionKeeper"));

	// *Also* immediately inject & refresh so you don’t depend on the callback timing:
	RegisterMenus();
	UToolMenus::Get()->RefreshAllWidgets();
}

void FConventionKeeperEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FConventionKeeperEditorStyle::Shutdown();
	FConventionKeeperEditorCommands::Unregister();
}

void FConventionKeeperEditorModule::PluginButtonClicked()
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	if (!ConventionKeeperSettings->Convention.Get())
	{
		return;
	}
	
	UConvention* Convention = ConventionKeeperSettings->Convention.GetDefaultObject();
	if (Convention)
	{
		Convention->ValidateFolderStructures();
	}
	
	// FText DialogText = FText::Format(
	// 						LOCTEXT("PluginButtonDialogText", "Path exists {0}"),
	// 						bExists);
	// FMessageDialog::Open(EAppMsgType::Ok, DialogText);
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
	}

	if (UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar"))
	{
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
		FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FConventionKeeperEditorCommands::Get().PluginAction));
		Entry.SetCommandList(PluginCommands);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FConventionKeeperEditorModule, ConventionKeeperEditor)
