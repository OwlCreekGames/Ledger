// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomain.h"

bool ULedgerDomain::HasName(const FName Name) const
{
	return State.Contains(Name);
}

TArray<FName> ULedgerDomain::GetNames() const
{
	TArray<FName> Names;
	State.GetKeys(Names);
	return Names;
}

bool ULedgerDomain::TrySetValue(const FName Name, const FLedgerValue& Value)
{
	State.Add(Name, Value);
	return true;
}

bool ULedgerDomain::TryGetValue(const FName Name, FLedgerValue& OutValue) const
{
	if (const FLedgerValue* Found = State.Find(Name))
	{
		OutValue = *Found;
		return true;
	}
	
	return false;
}

template<typename T>
bool ULedgerDomain::TrySet(const FName Name, const T& InValue)
{
	const FLedgerValue Value(InValue);
	return TrySetValue(Name, Value);
}

template<typename T>
bool ULedgerDomain::TryGet(const FName Name, T& OutValue) const
{
	FLedgerValue Value;
	if (TryGetValue(Name, Value))
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
