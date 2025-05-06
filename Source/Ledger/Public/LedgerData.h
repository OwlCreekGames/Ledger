// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LedgerData.generated.h"

class ULedgerDomainData;

/**
 * Configuration asset used to define all state domains in the registry.
 */
UCLASS(BlueprintType, meta = (DisplayName = "Ledger Configuration"))
class LEDGER_API ULedgerData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Ledger")
	TArray<TObjectPtr<ULedgerDomainData>> Domains;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};