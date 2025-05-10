#include "LedgerEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "LedgerEditorNodeFactory.h"
#include "LedgerEditorPinFactory.h"
#include "AssetEditors/FAssetTypeActions_LedgerSchemaConfig.h"
#include "Customizations/LedgerDomainConfigCustomization.h"
#include "Customizations/LedgerSchemaItemCustomization.h"

#define LOCTEXT_NAMESPACE "FLedgerEditorModule"

TSharedPtr<FLedgerEditorPinFactory> LedgerPinFactory;
TSharedPtr<FLedgerEditorNodeFactory> LedgerNodeFactory;

void FLedgerEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditor.RegisterCustomClassLayout(
		"LedgerDomainConfig",
		FOnGetDetailCustomizationInstance::CreateStatic(&FLedgerDomainConfigCustomization::MakeInstance)
		);
	
	PropertyEditor.RegisterCustomPropertyTypeLayout(
		"LedgerSchemaItem",
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FLedgerSchemaItemCustomization::MakeInstance)
	);

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const TSharedRef<IAssetTypeActions> Action = MakeShareable(new FAssetTypeActions_LedgerSchemaConfig);
	AssetTools.RegisterAssetTypeActions(Action);
}

void FLedgerEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FLedgerEditorModule, LedgerEditor)