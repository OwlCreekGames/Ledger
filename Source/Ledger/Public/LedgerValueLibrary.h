// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LedgerValue.h"
#include "LedgerValueLibrary.generated.h"

UCLASS()
class LEDGER_API ULedgerValueLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Ledger|Value")
	static ELedgerValueType GetType(const FLedgerValue& Value);

	UFUNCTION(BlueprintPure, Category = "Ledger|Value")
	static FString ToString(const FLedgerValue& Value);

	UFUNCTION(BlueprintPure, Category = "Ledger|Value")
	static bool IsNull(const FLedgerValue& Value);

	UFUNCTION(BlueprintPure, Category = "Ledger|Value", meta = (ExpandBoolAsExecs = "IsValid"))
	static int32 AsInt(const FLedgerValue& Value, bool& IsValid);

	UFUNCTION(BlueprintPure, Category = "Ledger|Value", meta = (ExpandBoolAsExecs = "IsValid"))
	static float AsFloat(const FLedgerValue& Value, bool& IsValid);

	UFUNCTION(BlueprintPure, Category = "Ledger|Value", meta = (ExpandBoolAsExecs = "IsValid"))
	static bool AsBool(const FLedgerValue& Value, bool& IsValid);

	UFUNCTION(BlueprintPure, Category = "Ledger|Value", meta = (ExpandBoolAsExecs = "IsValid"))
	static FString AsString(const FLedgerValue& Value, bool& IsValid);
};
