// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerSubsystem.h"

#include "LedgerDomainConfig.h"
#include "LedgerTypedDomain.h"
#include "Settings/LedgerEditorSettings.h"

TObjectPtr<ULedgerConfig> ULedgerSubsystem::TryLoadLedgerConfigAsset()
{
	if (const ULedgerEditorSettings* Settings = ULedgerEditorSettings::Get())
	{
		if (Settings->LedgerConfig.ToSoftObjectPath().IsValid())
		{
			if (ULedgerConfig* LedgerConfig = Cast<ULedgerConfig>(Settings->LedgerConfig.LoadSynchronous()))
			{
				return LedgerConfig;
			}
		}
	}
	
	return nullptr;
}

void ULedgerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	InitializeFromConfig(TryLoadLedgerConfigAsset());
}

TArray<FName> ULedgerSubsystem::GetDomainNames() const
{
	TArray<FName> Names;
	Domains.GetKeys(Names);
	return Names;
}

TArray<FName> ULedgerSubsystem::GetTypedDomainNames() const
{
	TArray<FName> Names;
	for (auto Domain: Domains)
	{
		if (Cast<ULedgerTypedDomain>(Domain.Value.Get()))
		{
			Names.Add(Domain.Key);
		}
	}
	return Names;
}

bool ULedgerSubsystem::TrySetValue(const FName DomainName, const FName Name, const FLedgerValue& Value)
{
	const TObjectPtr<ULedgerDomain>* Domain = Domains.Find(DomainName);
	if (Domain == nullptr)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Domain '%s' not found."), *DomainName.ToString());
		return false;
	}

	return Domain->Get()->TrySetValue(Name, Value);
}

bool ULedgerSubsystem::TryGetValue(const FName DomainName, const FName Name, FLedgerValue& OutValue) const
{
	const TObjectPtr<ULedgerDomain>* Domain = Domains.Find(DomainName);
	if (Domain == nullptr)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Domain '%s' not found."), *DomainName.ToString());
		return false;
	}
	
	return Domain->Get()->TryGetValue(Name, OutValue);
}

void ULedgerSubsystem::InitializeFromConfig(const TObjectPtr<ULedgerConfig>& LedgerConfig)
{
	if (LedgerConfig == nullptr)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: LedgerConfig is NULL; skipping InitializeDomains."));
		return;
	}

	for (const TObjectPtr<ULedgerDomainConfig>& DomainConfig : LedgerConfig->Domains)
	{
		if (DomainConfig->DomainName.IsNone())
		{
			UE_LOG(LogLedger, Warning, TEXT("Ledger: Skipping domain with empty name."));
			continue;
		}

		if (!DomainConfig->DomainClass)
		{
			UE_LOG(LogLedger, Warning, TEXT("Ledger: Skipping domain '%s' — no class assigned."), *DomainConfig->DomainName.ToString());
			continue;
		}
		
		ULedgerDomain* Domain = NewObject<ULedgerDomain>(this, DomainConfig->DomainClass);
		
		if (auto* TypedDomain = Cast<ULedgerTypedDomain>(Domain))
		{
			TypedDomain->InitializeFromSchema(DomainConfig->SchemaAsset);
		}

		Domain->DomainConfig = DomainConfig;
		RegisterDomain(DomainConfig->DomainName, Domain);
	}
}

void ULedgerSubsystem::RegisterDomain(const FName Name, const TObjectPtr<ULedgerDomain>& Domain)
{
	checkf(!Domains.Contains(Name), TEXT("Ledger: Domain '%s' already registered."), *Name.ToString());
	
	Domains.Add(Name, Domain);
}

template<typename T>
bool ULedgerSubsystem::TrySet(const FName DomainName, const FName Name, const T& InValue)
{
	const FLedgerValue Value(InValue);
	return TrySetValue(DomainName, Name, Value);
}

template<typename T>
bool ULedgerSubsystem::TryGet(const FName DomainName, const FName Name, T& OutValue) const
{
	FLedgerValue Value;
	if (TryGetValue(DomainName, Name, Value))
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
