// Copyright Owl Creek Games. All Rights Reserved.


#include "AssetEditors/FAssetTypeActions_LedgerSchemaConfig.h"

#include "AssetEditors/LedgerSchemaConfigAssetEditor.h"
#include "LedgerSchemaConfig.h"

void FAssetTypeActions_LedgerSchemaConfig::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost)
{
	auto* Asset = Cast<ULedgerSchemaConfig>(InObjects[0]);
	if (Asset)
	{
		const TSharedRef<FLedgerSchemaConfigAssetEditor> Editor = MakeShareable(new FLedgerSchemaConfigAssetEditor);
		Editor->InitEditor(EToolkitMode::Standalone, ToolkitHost, Asset);
	}
}
