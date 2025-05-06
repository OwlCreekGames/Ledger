// Copyright Owl Creek Games. All Rights Reserved.


#include "LedgerLibrary.h"
#include "LedgerSubsystem.h"
#include "Engine/World.h"

namespace
{
	ULedgerSubsystem* GetWorldStateSubsystem(const UObject* WorldContextObject)
	{
		if (!WorldContextObject) return nullptr;
		if (const UWorld* World = WorldContextObject->GetWorld())
		{
			return World->GetSubsystem<ULedgerSubsystem>();
		}
		return nullptr;
	}
}

void ULedgerLibrary::TryGetInt(UObject* WorldContextObject, const FName DomainName, const FName Key, int32& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<int32>(DomainName, Key, OutValue);
	}
}

void ULedgerLibrary::TryGetFloat(UObject* WorldContextObject, const FName DomainName, const FName Key, float& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<float>(DomainName, Key, OutValue);
	}
}

void ULedgerLibrary::TryGetBool(UObject* WorldContextObject, const FName DomainName, const FName Key, bool& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<bool>(DomainName, Key, OutValue);
	}
}

void ULedgerLibrary::TryGetString(UObject* WorldContextObject, const FName DomainName, const FName Key, FString& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<FString>(DomainName, Key, OutValue);
	}
}

void ULedgerLibrary::TrySetInt(UObject* WorldContextObject, const FName DomainName, const FName Key, int32 InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<int32>(DomainName, Key, InValue);
	}
}

void ULedgerLibrary::TrySetFloat(UObject* WorldContextObject, const FName DomainName, const FName Key, float InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<float>(DomainName, Key, InValue);
	}
}

void ULedgerLibrary::TrySetBool(UObject* WorldContextObject, const FName DomainName, const FName Key, bool InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<bool>(DomainName, Key, InValue);
	}
}

void ULedgerLibrary::TrySetString(UObject* WorldContextObject, const FName DomainName, const FName Key, const FString& InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<FString>(DomainName, Key, InValue);
	}
}
