// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomainLibrary.h"
#include "LedgerDomain.h"

void ULedgerDomainLibrary::TryGetInt(ULedgerDomain* Domain, FName Key, int32& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<int32>(Key, OutValue) : false;
}

void ULedgerDomainLibrary::TryGetFloat(ULedgerDomain* Domain, FName Key, float& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<float>(Key, OutValue) : false;
}

void ULedgerDomainLibrary::TryGetBool(ULedgerDomain* Domain, FName Key, bool& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<bool>(Key, OutValue) : false;
}

void ULedgerDomainLibrary::TryGetString(ULedgerDomain* Domain, FName Key, FString& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<FString>(Key, OutValue) : false;
}

void ULedgerDomainLibrary::TrySetInt(ULedgerDomain* Domain, FName Key, int32 InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<int32>(Key, InValue) : false;
}

void ULedgerDomainLibrary::TrySetFloat(ULedgerDomain* Domain, FName Key, float InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<float>(Key, InValue) : false;
}

void ULedgerDomainLibrary::TrySetBool(ULedgerDomain* Domain, FName Key, bool InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<bool>(Key, InValue) : false;
}

void ULedgerDomainLibrary::TrySetString(ULedgerDomain* Domain, FName Key, const FString& InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<FString>(Key, InValue) : false;
}
