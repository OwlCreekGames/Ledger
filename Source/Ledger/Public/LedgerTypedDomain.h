// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LedgerDomain.h"
#include "LedgerTypedDomain.generated.h"

struct FLedgerDomainSchemaEntry;
class ULedgerDomainSchemaData;
/**
 * 
 */
UCLASS()
class LEDGER_API ULedgerTypedDomain : public ULedgerDomain
{
	GENERATED_BODY()
public:

	virtual bool TrySetValue(FName Key, const FLedgerValue& Value) override;
	
	void InitializeFromSchema(ULedgerDomainSchemaData* InSchema);

private:
	UPROPERTY()
	TObjectPtr<ULedgerDomainSchemaData> Schema;
	
	TMap<FName, const FLedgerDomainSchemaEntry*> SchemaLookupMap;

	void InitializeSchemaLookupMap();
	void InitializeDefaultValues();
};
