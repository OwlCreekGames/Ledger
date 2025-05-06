#pragma once

#include "LedgerSubsystem.h"

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
		Subsystem->CreateDomain("TestDomain", ULedgerDomain::StaticClass());
		
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