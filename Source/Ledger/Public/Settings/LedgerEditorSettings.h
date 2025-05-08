// Copyright Owl Creek Games. All Rights Reserved.

// CreekStateEditorSettings.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LedgerConfig.h"
#include "LedgerEditorSettings.generated.h"

/**
 * Global settings for the State Registry plugin.
 * Configurable in Project Settings.
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Ledger"))
class LEDGER_API ULedgerEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category = "Ledger")
	TSoftObjectPtr<ULedgerConfig> LedgerConfig;
	
	static const ULedgerEditorSettings* Get()
	{
		return GetDefault<ULedgerEditorSettings>();
	}
};
