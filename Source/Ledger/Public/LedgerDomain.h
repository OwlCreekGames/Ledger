// Copyright Owl Creek Games. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LedgerValue.h"
#include "LedgerDomain.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class LEDGER_API ULedgerDomain : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ledger")
	virtual bool HasKey(FName Key) const;

	UFUNCTION(BlueprintCallable, Category = "Ledger")
	virtual TArray<FName> GetKeys() const;

	virtual bool TrySetValue(const FName Key, const FLedgerValue& Value);
	bool TryGetValue(const FName Key, FLedgerValue& OutValue) const;
	
	template<typename T>
	bool TrySet(const FName Key, const T& InValue);
	
	template<typename T>
	bool TryGet(const FName Key, T& OutValue) const;

protected:

	UPROPERTY()
	TMap<FName, FLedgerValue> State;
};
