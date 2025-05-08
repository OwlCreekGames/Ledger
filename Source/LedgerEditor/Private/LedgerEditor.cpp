#include "LedgerEditor.h"

#include "LedgerDomainConfigCustomization.h"
#include "LedgerEditorNodeFactory.h"
#include "LedgerEditorPinFactory.h"

#define LOCTEXT_NAMESPACE "FLedgerEditorModule"

TSharedPtr<FLedgerEditorPinFactory> LedgerPinFactory;
TSharedPtr<FLedgerEditorNodeFactory> LedgerNodeFactory;

void FLedgerEditorModule::StartupModule()
{
	// LedgerPinFactory = MakeShareable(new FLedgerEditorPinFactory());
	// FEdGraphUtilities::RegisterVisualPinFactory(LedgerPinFactory);
	
	// LedgerNodeFactory = MakeShareable(new FLedgerEditorNodeFactory());
	// FEdGraphUtilities::RegisterVisualNodeFactory(LedgerNodeFactory);
	
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditor.RegisterCustomClassLayout(
		"LedgerDomainConfig",
		FOnGetDetailCustomizationInstance::CreateStatic(&FLedgerDomainConfigCustomization::MakeInstance)
		);
	
	// PropertyEditor.RegisterCustomPropertyTypeLayout(
	// 	"LedgerSchemaEntry",
	// 	FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FLedgerSchemaEntryCustomization::MakeInstance)
	// );
}

void FLedgerEditorModule::ShutdownModule()
{
	// FEdGraphUtilities::UnregisterVisualPinFactory(LedgerPinFactory);
	// LedgerPinFactory.Reset();

	// FEdGraphUtilities::UnregisterVisualNodeFactory(LedgerNodeFactory);
	// LedgerNodeFactory.Reset();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FLedgerEditorModule, LedgerEditor)