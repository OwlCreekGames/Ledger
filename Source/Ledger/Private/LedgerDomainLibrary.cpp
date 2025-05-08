// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomainLibrary.h"
#include "LedgerDomain.h"

void ULedgerDomainLibrary::TryGetInt(ULedgerDomain* Domain, FName Name, int32& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<int32>(Name, OutValue) : false;
}

void ULedgerDomainLibrary::TryGetFloat(ULedgerDomain* Domain, FName Name, float& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<float>(Name, OutValue) : false;
}

void ULedgerDomainLibrary::TryGetBool(ULedgerDomain* Domain, FName Name, bool& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<bool>(Name, OutValue) : false;
}

void ULedgerDomainLibrary::TryGetString(ULedgerDomain* Domain, FName Name, FString& OutValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TryGet<FString>(Name, OutValue) : false;
}

void ULedgerDomainLibrary::TrySetInt(ULedgerDomain* Domain, FName Name, int32 InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<int32>(Name, InValue) : false;
}

void ULedgerDomainLibrary::TrySetFloat(ULedgerDomain* Domain, FName Name, float InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<float>(Name, InValue) : false;
}

void ULedgerDomainLibrary::TrySetBool(ULedgerDomain* Domain, FName Name, bool InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<bool>(Name, InValue) : false;
}

void ULedgerDomainLibrary::TrySetString(ULedgerDomain* Domain, FName Name, const FString& InValue, bool& bSuccess)
{
	bSuccess = Domain ? Domain->TrySet<FString>(Name, InValue) : false;
}
