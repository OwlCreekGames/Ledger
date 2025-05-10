// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "AssetTypeActions_Base.h"
#include "LedgerSchemaConfig.h"

class FAssetTypeActions_LedgerSchemaConfig final : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_LedgerSchemaConfig", "Ledger Schema Config"); }
	virtual FColor GetTypeColor() const override { return FColor(0, 153, 204); }
	virtual UClass* GetSupportedClass() const override { return ULedgerSchemaConfig::StaticClass(); }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost) override;
};
