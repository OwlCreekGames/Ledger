// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerValueLibrary.h"

ELedgerValueType ULedgerValueLibrary::GetType(const FLedgerValue& Value)
{
	return Value.GetType();
}

FString ULedgerValueLibrary::ToString(const FLedgerValue& Value)
{
	return Value.ToString();
}

bool ULedgerValueLibrary::IsNull(const FLedgerValue& Value)
{
	return Value.GetType() == ELedgerValueType::Null;
}

int32 ULedgerValueLibrary::AsInt(const FLedgerValue& Value, bool& IsValid)
{
	int32 Out;
	IsValid = Value.TryGet(Out);
	return IsValid ? Out : 0;
}

float ULedgerValueLibrary::AsFloat(const FLedgerValue& Value, bool& IsValid)
{
	float Out;
	IsValid = Value.TryGet(Out);
	return IsValid ? Out : 0.f;
}

bool ULedgerValueLibrary::AsBool(const FLedgerValue& Value, bool& IsValid)
{
	bool Out;
	IsValid = Value.TryGet(Out);
	return IsValid ? Out : false;
}

FString ULedgerValueLibrary::AsString(const FLedgerValue& Value, bool& IsValid)
{
	FString Out;
	IsValid = Value.TryGet(Out);
	return IsValid ? Out : FString();
}
