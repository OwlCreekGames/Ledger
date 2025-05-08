// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LedgerSubsystem.generated.h"

class ULedgerSchemaConfig;
struct FLedgerValue;
class ULedgerDomain;
class ULedgerConfig;

/**
 * 
 */
UCLASS()
class LEDGER_API ULedgerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void InitializeFromConfig(const TObjectPtr<ULedgerConfig>& LedgerConfig);
	
	UFUNCTION(BlueprintCallable, Category = "Ledger")
	virtual TArray<FName> GetDomainNames() const;

	UFUNCTION(BlueprintCallable, Category = "Ledger")
	virtual TArray<FName> GetTypedDomainNames() const;
	
	bool TrySetValue(FName DomainName, FName Name, const FLedgerValue& Value);
	bool TryGetValue(FName DomainName, FName Name, FLedgerValue& OutValue) const;
	
	template<typename T>
	bool TrySet(FName DomainName, FName Name, const T& InValue);

	template<typename T>
	bool TryGet(FName DomainName, FName Name, T& OutValue) const;
	
private:
	UPROPERTY()
	TMap<FName, TObjectPtr<ULedgerDomain>> Domains;
	
	static TObjectPtr<ULedgerConfig> TryLoadLedgerConfigAsset();
	void RegisterDomain(const FName Name, const TObjectPtr<ULedgerDomain>& Domain);
};
