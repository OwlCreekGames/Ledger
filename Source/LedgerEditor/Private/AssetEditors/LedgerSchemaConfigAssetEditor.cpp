// Copyright Owl Creek Games. All Rights Reserved.

#include "AssetEditors/LedgerSchemaConfigAssetEditor.h"

#include "EditorValidatorSubsystem.h"
#include "LedgerSchemaConfig.h"
#include "PropertyEditorModule.h"
#include "ToolMenus.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Misc/DataValidation.h"
#include "Widgets/Docking/SDockTab.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Notifications/SNotificationList.h"

static const FName DetailsTabId("LedgerSchemaEditor_Details");

#define LOCTEXT_NAMESPACE "FLedgerSchemaConfigAssetEditor"

void FLedgerSchemaConfigAssetEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ULedgerSchemaConfig* InAsset)
{
	EditingAsset = InAsset;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bUpdatesFromSelection = false;
	
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(InAsset);

	CommandList = MakeShared<FUICommandList>();
	
	ExtendToolbar();
	
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("LedgerSchemaEditor_Layout")
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewStack()
				->AddTab(DetailsTabId, ETabState::OpenedTab)
				->SetHideTabWell(false)
			)
		);

	InitAssetEditor(Mode, InitToolkitHost, GetToolkitFName(), Layout, true, true, TArray<UObject*>{ InAsset });
}

void FLedgerSchemaConfigAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateRaw(this, &FLedgerSchemaConfigAssetEditor::SpawnDetailsTab))
		.SetDisplayName(LOCTEXT("DetailsTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FLedgerSchemaConfigAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(DetailsTabId);
}

TSharedRef<SDockTab> FLedgerSchemaConfigAssetEditor::SpawnDetailsTab(const FSpawnTabArgs& Args) const
{
	return SNew(SDockTab)
		.Label(LOCTEXT("DetailsTab", "Details"))
		.CanEverClose(false)
		[
			DetailsView.ToSharedRef()
		];
}

FText FLedgerSchemaConfigAssetEditor::GetToolkitName() const
{
	if (const UObject* Asset = GetEditingObject())
	{
		return FText::Format(
			LOCTEXT("LedgerSchemaEditorToolkitName", "{0} ({1})"),
			FText::FromString(Asset->GetName()),
			GetBaseToolkitName()
		);
	}
	return LOCTEXT("LedgerSchemaEditorToolkitNameUnknown", "Unknown (Ledger Schema Config)");
}

FText FLedgerSchemaConfigAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("LedgerSchemaEditorName", "Ledger Schema Config");
}

void FLedgerSchemaConfigAssetEditor::ExtendToolbar()
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();
	Extender->AddToolBarExtension(
		"Asset", EExtensionHook::After, CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FLedgerSchemaConfigAssetEditor::FillToolbar)
	);
	AddToolbarExtender(Extender);
}

void FLedgerSchemaConfigAssetEditor::FillToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.AddToolBarButton(
		FUIAction(FExecuteAction::CreateRaw(this, &FLedgerSchemaConfigAssetEditor::OnValidateClicked)),
		NAME_None,
		LOCTEXT("ValidateButton", "Validate"),
		LOCTEXT("ValidateTooltip", "Validate the schema data."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Check")
	);
}

void FLedgerSchemaConfigAssetEditor::OnValidateClicked()
{
#if WITH_EDITOR

	const UEditorValidatorSubsystem* ValidatorSubsystem = GEditor->GetEditorSubsystem<UEditorValidatorSubsystem>();
	if (ValidatorSubsystem)
	{
		// Prepare the validation settings (mirrors what Save/Validation uses)
		FValidateAssetsSettings Settings;
		Settings.ValidationUsecase = EDataValidationUsecase::Manual;

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		const FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(EditingAsset->GetPathName());
		
		const TArray AssetsToValidate = { AssetData };
		FValidateAssetsResults Results;

		const int32 Result = ValidatorSubsystem->ValidateAssetsWithSettings(AssetsToValidate, Settings, Results);
		if (Result == 0)
		{
			FNotificationInfo Info(FText::FromString("Validation passed!"));
			Info.ExpireDuration = 2.5f;
			Info.bUseThrobber = false;
			FSlateNotificationManager::Get().AddNotification(Info);
		}
	}
#endif
}

#undef LOCTEXT_NAMESPACE
