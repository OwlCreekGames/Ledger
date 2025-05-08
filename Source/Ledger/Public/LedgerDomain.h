// Copyright Owl Creek Games. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LedgerValue.h"
#include "LedgerDomain.generated.h"

class ULedgerDomainConfig;
/**
 *
 */
UCLASS(Blueprintable)
class LEDGER_API ULedgerDomain : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Ledger")
	TObjectPtr<ULedgerDomainConfig> DomainConfig;
	
	UFUNCTION(BlueprintCallable, Category = "Ledger")
	virtual bool HasName(FName Name) const;

	UFUNCTION(BlueprintCallable, Category = "Ledger")
	virtual TArray<FName> GetNames() const;

	virtual bool TrySetValue(const FName Name, const FLedgerValue& Value);
	bool TryGetValue(const FName Name, FLedgerValue& OutValue) const;
	
	template<typename T>
	bool TrySet(const FName Name, const T& InValue);
	
	template<typename T>
	bool TryGet(const FName Name, T& OutValue) const;

protected:

	UPROPERTY()
	TMap<FName, FLedgerValue> State;
};
