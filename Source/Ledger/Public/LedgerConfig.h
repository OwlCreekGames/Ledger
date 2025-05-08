// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LedgerConfig.generated.h"

class ULedgerDomainConfig;

/**
 * Configuration asset used to define all state domains in the registry.
 */
UCLASS(BlueprintType, meta = (DisplayName = "Ledger Config"))
class LEDGER_API ULedgerConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Ledger")
	TArray<TObjectPtr<ULedgerDomainConfig>> Domains;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};