#pragma once

#include "LedgerDomainConfig.h"
#include "LedgerSubsystem.h"
#include "Settings/LedgerEditorSettings.h"

#if WITH_DEV_AUTOMATION_TESTS

class FLedgerSubsystemTestFixture
{
public:
	UWorld* TestWorld = nullptr;
	ULedgerSubsystem* Subsystem = nullptr;

	FLedgerSubsystemTestFixture()
	{
		TestWorld = UWorld::CreateWorld(EWorldType::Game, false);
		check(TestWorld);
		
		FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);
		WorldContext.SetCurrentWorld(TestWorld);
		
		Subsystem = TestWorld->GetSubsystem<ULedgerSubsystem>();
		
		const auto Domain = NewObject<ULedgerDomainConfig>();
		Domain->DomainName = FName("TestDomain");
		Domain->DomainClass = ULedgerDomain::StaticClass();

		const auto Config = NewObject<ULedgerConfig>();
		Config->Domains.Add(Domain);
		
		Subsystem->InitializeFromConfig(Config);
		
		check(Subsystem);
	}

	~FLedgerSubsystemTestFixture()
	{
		if (TestWorld)
		{
			TestWorld->DestroyWorld(false);
			TestWorld = nullptr;
		}
	}
};

#endif //WITH_DEV_AUTOMATION_TESTS