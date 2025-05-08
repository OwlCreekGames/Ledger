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

void ULedgerLibrary::TryGetInt(UObject* WorldContextObject, const FName DomainName, const FName Name, int32& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<int32>(DomainName, Name, OutValue);
	}
}

void ULedgerLibrary::TryGetFloat(UObject* WorldContextObject, const FName DomainName, const FName Name, float& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<float>(DomainName, Name, OutValue);
	}
}

void ULedgerLibrary::TryGetBool(UObject* WorldContextObject, const FName DomainName, const FName Name, bool& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<bool>(DomainName, Name, OutValue);
	}
}

void ULedgerLibrary::TryGetString(UObject* WorldContextObject, const FName DomainName, const FName Name, FString& OutValue, bool& bSuccess)
{
	bSuccess = false;
	if (const ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TryGet<FString>(DomainName, Name, OutValue);
	}
}

void ULedgerLibrary::TrySetInt(UObject* WorldContextObject, const FName DomainName, const FName Name, int32 InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<int32>(DomainName, Name, InValue);
	}
}

void ULedgerLibrary::TrySetFloat(UObject* WorldContextObject, const FName DomainName, const FName Name, float InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<float>(DomainName, Name, InValue);
	}
}

void ULedgerLibrary::TrySetBool(UObject* WorldContextObject, const FName DomainName, const FName Name, bool InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<bool>(DomainName, Name, InValue);
	}
}

void ULedgerLibrary::TrySetString(UObject* WorldContextObject, const FName DomainName, const FName Name, const FString& InValue, bool& bSuccess)
{
	bSuccess = false;
	if (ULedgerSubsystem* Registry = GetWorldStateSubsystem(WorldContextObject))
	{
		bSuccess = Registry->TrySet<FString>(DomainName, Name, InValue);
	}
}
