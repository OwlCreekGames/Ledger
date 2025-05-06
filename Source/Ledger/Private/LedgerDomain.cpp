// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomain.h"

bool ULedgerDomain::HasKey(const FName Key) const
{
	return State.Contains(Key);
}

TArray<FName> ULedgerDomain::GetKeys() const
{
	TArray<FName> Keys;
	State.GetKeys(Keys);
	return Keys;
}

bool ULedgerDomain::TrySetValue(const FName Key, const FLedgerValue& Value)
{
	State.Add(Key, Value);
	return true;
}

bool ULedgerDomain::TryGetValue(const FName Key, FLedgerValue& OutValue) const
{
	if (const FLedgerValue* Found = State.Find(Key))
	{
		OutValue = *Found;
		return true;
	}
	
	return false;
}

template<typename T>
bool ULedgerDomain::TrySet(const FName Key, const T& InValue)
{
	const FLedgerValue Value(InValue);
	return TrySetValue(Key, Value);
}

template<typename T>
bool ULedgerDomain::TryGet(const FName Key, T& OutValue) const
{
	FLedgerValue Value;
	if (TryGetValue(Key, Value))
	{
		return Value.TryGet(OutValue);
	}
	return false;
}

template bool ULedgerDomain::TrySet<int32>(FName, const int32&);
template bool ULedgerDomain::TrySet<float>(FName, const float&);
template bool ULedgerDomain::TrySet<bool>(FName, const bool&);
template bool ULedgerDomain::TrySet<FString>(FName, const FString&);

template bool ULedgerDomain::TryGet<int32>(FName, int32&) const;
template bool ULedgerDomain::TryGet<float>(FName, float&) const;
template bool ULedgerDomain::TryGet<bool>(FName, bool&) const;
template bool ULedgerDomain::TryGet<FString>(FName, FString&) const;
