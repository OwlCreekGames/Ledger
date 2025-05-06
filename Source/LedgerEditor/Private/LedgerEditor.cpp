#include "LedgerEditor.h"

#include "LedgerDomainDataCustomization.h"
#include "LedgerDomainSchemaEntryCustomization.h"

#define LOCTEXT_NAMESPACE "FLedgerEditorModule"

void FLedgerEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditor.RegisterCustomClassLayout(
		"LedgerDomainData",
		FOnGetDetailCustomizationInstance::CreateStatic(&FLedgerDomainDataCustomization::MakeInstance));
	
	PropertyEditor.RegisterCustomPropertyTypeLayout(
		"LedgerSchemaEntry",
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FLedgerDomainSchemaEntryCustomization::MakeInstance)
	);

}

void FLedgerEditorModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FLedgerEditorModule, LedgerEditor)