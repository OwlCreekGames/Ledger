// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LedgerValue.h"
#include "LedgerSchemaConfig.generated.h"

USTRUCT(BlueprintType)
struct FLedgerSchemaItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Schema")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Schema")
	ELedgerValueType Type = ELedgerValueType::Null;

	UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayName = "Default Value", EditCondition = "Type == ELedgerValueType::Int32", EditConditionHides))
	int32 DefaultInt32 = 0;

	UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayName = "Default Value", EditCondition = "Type == ELedgerValueType::Float", EditConditionHides))
	float DefaultFloat = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayName = "Default Value", EditCondition = "Type == ELedgerValueType::Bool", EditConditionHides))
	bool DefaultBool = false;

	UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayName = "Default Value", EditCondition = "Type == ELedgerValueType::String", EditConditionHides))
	FString DefaultString;

	UPROPERTY(EditAnywhere, Category = "Schema")
	FString Description;
	
	FLedgerValue ToDefaultValue() const
	{
		switch (Type)
		{
			case ELedgerValueType::Int32: return FLedgerValue(DefaultInt32);
			case ELedgerValueType::Float: return FLedgerValue(DefaultFloat);
			case ELedgerValueType::Bool: return FLedgerValue(DefaultBool);
			case ELedgerValueType::String: return FLedgerValue(DefaultString);
			default: return FLedgerValue();
		}
	}
};

UCLASS(BlueprintType, meta = (DisplayName = "Ledger Domain Schema"))
class LEDGER_API ULedgerSchemaConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Schema")
	TArray<FLedgerSchemaItem> Items;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};