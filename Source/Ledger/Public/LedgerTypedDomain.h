// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LedgerDomain.h"
#include "LedgerTypedDomain.generated.h"

struct FLedgerSchemaItem;
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
	
	TMap<FName, const FLedgerSchemaItem*> SchemaLookupMap;

	void InitializeSchemaLookupMap();
	void InitializeDefaultValues();
};
