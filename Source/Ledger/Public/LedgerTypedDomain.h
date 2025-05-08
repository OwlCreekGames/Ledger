// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LedgerDomain.h"
#include "LedgerTypedDomain.generated.h"

struct FLedgerSchemaRow;
class ULedgerSchemaConfig;

/**
 * 
 */
UCLASS()
class LEDGER_API ULedgerTypedDomain : public ULedgerDomain
{
	GENERATED_BODY()
public:

	virtual bool TrySetValue(FName Name, const FLedgerValue& Value) override;
	
	void InitializeFromSchema(ULedgerSchemaConfig* InSchema);

private:
	UPROPERTY()
	TObjectPtr<ULedgerSchemaConfig> Schema;
	
	TMap<FName, uint8*> SchemaRowMap;

	void InitializeSchemaLookupMap();
	void InitializeDefaultValues();
};
