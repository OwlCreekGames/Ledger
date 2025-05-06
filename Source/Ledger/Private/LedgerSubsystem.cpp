// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerSubsystem.h"

#include "LedgerDomainData.h"
#include "LedgerTypedDomain.h"
#include "Settings/LedgerEditorSettings.h"

TObjectPtr<ULedgerData> ULedgerSubsystem::TryLoadStateRegistryData()
{
	if (const ULedgerEditorSettings* Settings = ULedgerEditorSettings::Get())
	{
		if (Settings->WorldStateData.ToSoftObjectPath().IsValid())
		{
			if (ULedgerData* StateRegistryData = Cast<ULedgerData>(Settings->WorldStateData.LoadSynchronous()))
			{
				return StateRegistryData;
			}
		}
	}
	
	return nullptr;
}

void ULedgerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RuntimeRegistryData = TryLoadStateRegistryData();
	InitializeDomains(RuntimeRegistryData);
}

bool ULedgerSubsystem::CreateDomain(FName DomainName, TSubclassOf<ULedgerDomain> DomainClass)
{
	if (DomainName.IsNone())
	{
		UE_LOG(LogLedger, Warning, TEXT("CreateDomain: Domain name is None."));
		return false;
	}

	if (!DomainClass)
	{
		UE_LOG(LogLedger, Warning, TEXT("CreateDomain: Domain class is null."));
		return false;
	}

	ULedgerDomain* NewDomain = NewObject<ULedgerDomain>(this, DomainClass);
	RegisterDomain(DomainName, NewDomain);
	return true;
}

bool ULedgerSubsystem::CreateDomainWithSchema(FName DomainName, TSubclassOf<ULedgerDomain> DomainClass, ULedgerDomainSchemaData* Schema)
{
	checkf(false, TEXT("Not implemented"));

	return false;
	
	// if (ULedgerTypedDomain* Typed = Cast<ULedgerTypedDomain>(NewDomain))
	// {
	// 	Typed->InitializeFromSchema(Schema);
	// }

}


bool ULedgerSubsystem::TrySetValue(const FName DomainName, const FName Key, const FLedgerValue& Value)
{
	const TObjectPtr<ULedgerDomain>* Domain = Domains.Find(DomainName);
	if (Domain == nullptr)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Domain '%s' not found."), *DomainName.ToString());
		return false;
	}

	return Domain->Get()->TrySetValue(Key, Value);
}

bool ULedgerSubsystem::TryGetValue(const FName DomainName, const FName Key, FLedgerValue& OutValue) const
{
	const TObjectPtr<ULedgerDomain>* Domain = Domains.Find(DomainName);
	if (Domain == nullptr)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Domain '%s' not found."), *DomainName.ToString());
		return false;
	}
	
	return Domain->Get()->TryGetValue(Key, OutValue);
}

void ULedgerSubsystem::InitializeDomains(const TObjectPtr<ULedgerData>& StateRegistryData)
{
	if (!StateRegistryData)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: No world state configuration data is specified."));
		return;
	}

	for (const TObjectPtr<ULedgerDomainData>& DomainAsset : StateRegistryData->Domains)
	{
		if (DomainAsset->DomainName.IsNone())
		{
			UE_LOG(LogLedger, Warning, TEXT("Ledger: Skipping domain with empty name."));
			continue;
		}

		if (!DomainAsset->DomainClass)
		{
			UE_LOG(LogLedger, Warning, TEXT("Ledger: Skipping domain '%s' — no class assigned."), *DomainAsset->DomainName.ToString());
			continue;
		}
		
		ULedgerDomain* Domain = NewObject<ULedgerDomain>(this, DomainAsset->DomainClass);

		/*
		if (auto* TypedDomain = Cast<UCreekTypedStateDomain>(Domain))
		{
			TypedDomain->InitializeFromSchema(DomainAsset->SchemaAsset);
		}
		*/

		RegisterDomain(DomainAsset->DomainName, Domain);
	}
}

void ULedgerSubsystem::RegisterDomain(const FName Name, const TObjectPtr<ULedgerDomain>& Domain)
{
	checkf(!Domains.Contains(Name), TEXT("Ledger: Domain '%s' already registered."), *Name.ToString());

	Domains.Add(Name, Domain);
}

template<typename T>
bool ULedgerSubsystem::TrySet(const FName DomainName, const FName Key, const T& InValue)
{
	const FLedgerValue Value(InValue);
	return TrySetValue(DomainName, Key, Value);
}

template<typename T>
bool ULedgerSubsystem::TryGet(const FName DomainName, const FName Key, T& OutValue) const
{
	FLedgerValue Value;
	if (TryGetValue(DomainName, Key, Value))
	{
		return Value.TryGet(OutValue);
	}
	
	return false;
}

template bool ULedgerSubsystem::TrySet<int32>(const FName, const FName, const int32&);
template bool ULedgerSubsystem::TrySet<float>(const FName, const FName, const float&);
template bool ULedgerSubsystem::TrySet<bool>(const FName, const FName, const bool&);
template bool ULedgerSubsystem::TrySet<FString>(const FName, const FName, const FString&);

template bool ULedgerSubsystem::TryGet<int32>(const FName, const FName, int32&) const;
template bool ULedgerSubsystem::TryGet<float>(const FName, const FName, float&) const;
template bool ULedgerSubsystem::TryGet<bool>(const FName, const FName, bool&) const;
template bool ULedgerSubsystem::TryGet<FString>(const FName, const FName, FString&) const;
