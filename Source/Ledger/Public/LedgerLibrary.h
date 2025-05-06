// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LedgerValue.h"
#include "LedgerLibrary.generated.h"

/**
 * Blueprint-accessible global state access functions.
 * Routes through the ULedgerSubsystem.
 */
UCLASS()
class LEDGER_API ULedgerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TryGetInt(UObject* WorldContextObject, const FName DomainName, const FName Key, int32& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TrySetInt(UObject* WorldContextObject, const FName DomainName, const FName Key, int32 InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TryGetFloat(UObject* WorldContextObject, const FName DomainName, const FName Key, float& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TrySetFloat(UObject* WorldContextObject, const FName DomainName, const FName Key, float InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TryGetBool(UObject* WorldContextObject, const FName DomainName, const FName Key, bool& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TrySetBool(UObject* WorldContextObject, const FName DomainName, const FName Key, bool InValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TryGetString(UObject* WorldContextObject, const FName DomainName, const FName Key, FString& OutValue, bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ledger", meta = (WorldContext = "WorldContextObject", ExpandBoolAsExecs = "bSuccess"))
	static void TrySetString(UObject* WorldContextObject, const FName DomainName, const FName Key, const FString& InValue, bool& bSuccess);
};
