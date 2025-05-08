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
	static void TryGetInt(ULedgerDomain* Domain, FName Name, int32& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetFloat(ULedgerDomain* Domain, FName Name, float& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetBool(ULedgerDomain* Domain, FName Name, bool& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TryGetString(ULedgerDomain* Domain, FName Name, FString& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetInt(ULedgerDomain* Domain, FName Name, int32 InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetFloat(ULedgerDomain* Domain, FName Name, float InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetBool(ULedgerDomain* Domain, FName Name, bool InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger|Domain", meta = (ExpandBoolAsExecs = "bSuccess"))
	static void TrySetString(ULedgerDomain* Domain, FName Name, const FString& InValue, bool& bSuccess);
};
