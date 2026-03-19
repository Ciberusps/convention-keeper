// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogConventionKeeper, Log, All);

class FObjectPostSaveContext;
class UPackage;
class FToolBarBuilder;
class FMenuBuilder;
class IAssetTypeActions;
class FExtender;

class FConventionKeeperEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	/** ~IModuleInterface implementation */
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	/** Runs Convention Rule Coverage analysis and reports to Message Log. */
	void RunCoverageTest();
	/** Runs Convention Compliance analysis and reports to Message Log. */
	void RunComplianceTest();
	
private:
	void RegisterMenus();

	bool CheckAssetPathExists(const FString& PackagePath);

	void RegisterAssetTypeActions();
	void UnregisterAssetTypeActions();

	void RegisterContentBrowserExtenders();
	void UnregisterContentBrowserExtenders();

	void OnPackageSaved(const FString& PackageFileName, UPackage* Package, const FObjectPostSaveContext& SaveContext);
	void ValidateSavedPackages();

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TArray<TSharedPtr<class IAssetTypeActions>> RegisteredAssetTypeActions;
	FDelegateHandle ContentBrowserPathExtenderDelegateHandle;
	FDelegateHandle ContentBrowserAssetExtenderDelegateHandle;
	FDelegateHandle PackageSavedDelegateHandle;

	TArray<FString> SavedPackagePathsToValidate;
};
