// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LedgerDomain.h"
#include "LedgerDomainSchemaData.h"
#include "LedgerDomainData.generated.h"

/**
 * Represents a single domain configuration for use in a state registry.
 * Can be reused across registries or configured independently.
 */
UCLASS(BlueprintType, meta = (DisplayName = "Ledger Domain"))
class LEDGER_API ULedgerDomainData : public UDataAsset
{
	GENERATED_BODY()

public:

	// Name used to register the domain in the state registry
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Domain")
	FName DomainName;

	// Domain class (must inherit from UCreekStateDomain)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Domain", meta = (MustImplement = "/Script/Ledger.CreekStateDomain"))
	TSubclassOf<ULedgerDomain> DomainClass = ULedgerDomain::StaticClass();

	// Optional schema (only used if the domain class requires one)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Domain")
	TObjectPtr<ULedgerDomainSchemaData> SchemaAsset = nullptr;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};

