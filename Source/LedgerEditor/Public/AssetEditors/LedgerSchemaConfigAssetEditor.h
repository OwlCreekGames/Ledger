#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class ULedgerSchemaConfig;

class FLedgerSchemaConfigAssetEditor final : public FAssetEditorToolkit
{
public:
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ULedgerSchemaConfig* InAsset);

	// Required overrides
	virtual FName GetToolkitFName() const override { return FName("LedgerSchemaEditor"); }
	virtual FText GetToolkitName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("LedgerSchema"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	
	// Tabs
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	TSharedRef<SDockTab> SpawnDetailsTab(const FSpawnTabArgs& Args) const;
	void ExtendToolbar();
	void FillToolbar(FToolBarBuilder& ToolbarBuilder);
	void OnValidateClicked();

	TWeakObjectPtr<ULedgerSchemaConfig> EditingAsset;
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<FUICommandList> CommandList;
};
