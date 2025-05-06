// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LedgerDomainLibrary.generated.h"

class ULedgerDomain;

UCLASS()
class LEDGER_API ULedgerDomainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetInt(ULedgerDomain* Domain, FName Key, int32& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetFloat(ULedgerDomain* Domain, FName Key, float& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetBool(ULedgerDomain* Domain, FName Key, bool& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetString(ULedgerDomain* Domain, FName Key, FString& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetInt(ULedgerDomain* Domain, FName Key, int32 InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetFloat(ULedgerDomain* Domain, FName Key, float InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetBool(ULedgerDomain* Domain, FName Key, bool InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetString(ULedgerDomain* Domain, FName Key, const FString& InValue, bool& bSuccess);
};
