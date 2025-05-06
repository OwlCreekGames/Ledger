// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LedgerSubsystem.generated.h"

class ULedgerDomainSchemaData;
struct FLedgerValue;
class ULedgerDomain;
class ULedgerData;

/**
 * 
 */
UCLASS()
class LEDGER_API ULedgerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "World State")
	bool CreateDomain(FName DomainName, TSubclassOf<ULedgerDomain> DomainClass);

	UFUNCTION(BlueprintCallable, Category = "World State")
	bool CreateDomainWithSchema(FName DomainName, TSubclassOf<ULedgerDomain> DomainClass, ULedgerDomainSchemaData* Schema);

	
	bool TrySetValue(FName DomainName, FName Key, const FLedgerValue& Value);
	bool TryGetValue(FName DomainName, FName Key, FLedgerValue& OutValue) const;
	
	template<typename T>
	bool TrySet(FName DomainName, FName Key, const T& InValue);

	template<typename T>
	bool TryGet(FName DomainName, FName Key, T& OutValue) const;
	
private:
	UPROPERTY()
	TObjectPtr<ULedgerData> RuntimeRegistryData;
	
	UPROPERTY()
	TMap<FName, TObjectPtr<ULedgerDomain>> Domains;
	
	static TObjectPtr<ULedgerData> TryLoadStateRegistryData();
	void InitializeDomains(const TObjectPtr<ULedgerData>& StateRegistryData);
	void RegisterDomain(const FName Name, const TObjectPtr<ULedgerDomain>& Domain);
};
