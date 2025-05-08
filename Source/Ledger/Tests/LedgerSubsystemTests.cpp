// Copyright Owl Creek Games. All Rights Reserved.

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "LedgerSubsystem.h"
#include "LedgerDomain.h"
#include "LedgerSubsystemTestFixture.h"
#include "LedgerTypedDomain.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_GetDomainNames,
    "Ledger.LedgerSubsystem.GetDomainNames",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_GetDomainNames::RunTest(const FString&)
{
    // Setup
    ULedgerSubsystem* Subsystem = NewObject<ULedgerSubsystem>();

    const auto Domain1 = NewObject<ULedgerDomainConfig>();
    Domain1->DomainName = FName("TestDomain1");
    Domain1->DomainClass = ULedgerDomain::StaticClass();

    const auto Domain2 = NewObject<ULedgerDomainConfig>();
    Domain2->DomainName = FName("TestDomain2");
    Domain2->DomainClass = ULedgerDomain::StaticClass();

    const auto Domain3 = NewObject<ULedgerDomainConfig>();
    Domain3->DomainName = FName("TestDomain3");
    Domain3->DomainClass = ULedgerTypedDomain::StaticClass();
    
    const auto Config = NewObject<ULedgerConfig>();
    Config->Domains.Add(Domain1);
    Config->Domains.Add(Domain2);
    Config->Domains.Add(Domain3);

    Subsystem->InitializeFromConfig(Config);
    
    // Act
    const TArray<FName> Names = Subsystem->GetDomainNames();

    // Assert
    TestEqual(TEXT("Should return 3 names"), Names.Num(), 3);
    TestTrue(TEXT("Should contain 'TestDomain1'"), Names.Contains(TEXT("TestDomain1")));
    TestTrue(TEXT("Should contain 'TestDomain2'"), Names.Contains(TEXT("TestDomain2")));
    TestTrue(TEXT("Should contain 'TestDomain3'"), Names.Contains(TEXT("TestDomain3")));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_GetTypedDomainNames,
    "Ledger.LedgerSubsystem.GetTypedDomainNames",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_GetTypedDomainNames::RunTest(const FString&)
{
    // Setup
    ULedgerSubsystem* Subsystem = NewObject<ULedgerSubsystem>();
    
    const auto Domain1 = NewObject<ULedgerDomainConfig>();
    Domain1->DomainName = FName("TestDomain1");
    Domain1->DomainClass = ULedgerDomain::StaticClass();

    const auto Domain2 = NewObject<ULedgerDomainConfig>();
    Domain2->DomainName = FName("TestDomain2");
    Domain2->DomainClass = ULedgerDomain::StaticClass();

    const auto Domain3 = NewObject<ULedgerDomainConfig>();
    Domain3->DomainName = FName("TestDomain3");
    Domain3->DomainClass = ULedgerTypedDomain::StaticClass();
    
    const auto Config = NewObject<ULedgerConfig>();
    Config->Domains.Add(Domain1);
    Config->Domains.Add(Domain2);
    Config->Domains.Add(Domain3);

    Subsystem->InitializeFromConfig(Config);
    
    // Act
    const TArray<FName> Names = Subsystem->GetTypedDomainNames();

    // Assert
    TestEqual(TEXT("Should return 1 names"), Names.Num(), 1);
    TestTrue(TEXT("Should contain 'TestDomain3'"), Names.Contains(TEXT("TestDomain3")));

    return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TrySetValue_ValidDomain,
    "Ledger.LedgerSubsystem.TrySetValue.ValidDomain",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TrySetValue_ValidDomain::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    // Act
    const bool bSet = Fixture.Subsystem->TrySetValue(TEXT("TestDomain"), TEXT("TestName"), FLedgerValue(42));
    
    // Assert
    TestTrue(TEXT("Should successfully set value for registered domain"), bSet);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TrySetValue_InvalidDomain,
    "Ledger.LedgerSubsystem.TrySetValue.InvalidDomain",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TrySetValue_InvalidDomain::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);

    // Act
    const bool bSet = Fixture.Subsystem->TrySetValue(TEXT("InvalidDomain"), TEXT("TestName"), FLedgerValue(42));
    
    // Assert
    TestFalse(TEXT("Should not set value for nonexistent domain"), bSet);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TrySet_Int32,
    "Ledger.LedgerSubsystem.TrySet.Int32",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TrySet_Int32::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Value");

    // Act
    const bool bSet = Fixture.Subsystem->TrySet<int32>(Domain, Name, 100);

    // Assert
    TestTrue(TEXT("TrySet<int32> should succeed"), bSet);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TrySet_Float,
    "Ledger.LedgerSubsystem.TrySet.Float",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TrySet_Float::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Value");

    // Act
    const bool bSet = Fixture.Subsystem->TrySet<float>(Domain, Name, 3.14f);

    // Assert
    TestTrue(TEXT("TrySet<float> should succeed"), bSet);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TrySet_Bool,
    "Ledger.LedgerSubsystem.TrySet.Bool",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TrySet_Bool::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Visited");

    // Act
    const bool bSet = Fixture.Subsystem->TrySet<bool>(Domain, Name, true);

    // Assert
    TestTrue(TEXT("TrySet<bool> should succeed"), bSet);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TrySet_String,
    "Ledger.LedgerSubsystem.TrySet.String",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TrySet_String::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Note");

    // Act
    const bool bSet = Fixture.Subsystem->TrySet<FString>(Domain, Name, TEXT("Hello world"));

    // Assert
    TestTrue(TEXT("TrySet<FString> should succeed"), bSet);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TryGet_ValidDomain,
    "Ledger.LedgerSubsystem.TryGet.ValidDomain",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TryGet_ValidDomain::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);

    // Act
    FLedgerValue OutValue;
    const bool bGot = Fixture.Subsystem->TryGetValue(TEXT("Domain"), TEXT("Name"), OutValue);

    // Assert
    TestFalse(TEXT("Should not retrieve value from nonexistent domain"), bGot);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLedgerSubsystem_TryGet_InvalidDomain,
    "Ledger.LedgerSubsystem.TryGet.InvalidDomain",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TryGet_InvalidDomain::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);

    // Act
    FLedgerValue OutValue;
    const bool bGot = Fixture.Subsystem->TryGetValue(TEXT("InvalidDomain"), TEXT("Name"), OutValue);

    // Assert
    TestFalse(TEXT("Should not retrieve value from nonexistent domain"), bGot);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TryGet_Int32,
    "Ledger.LedgerSubsystem.TryGet.Int32",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TryGet_Int32::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Score");

    Fixture.Subsystem->TrySet<int32>(Domain, Name, 77);

    // Act
    int32 Value;
    const bool bGot = Fixture.Subsystem->TryGet<int32>(Domain, Name, Value);

    // Assert
    TestTrue(TEXT("TryGet<int32> should succeed"), bGot);
    TestEqual(TEXT("Value should be 77"), Value, 77);
    
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TryGet_Float,
    "Ledger.LedgerSubsystem.TryGet.Float",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TryGet_Float::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Speed");

    Fixture.Subsystem->TrySet<float>(Domain, Name, 2.5f);

    // Act
    float Value;
    const bool bGot = Fixture.Subsystem->TryGet<float>(Domain, Name, Value);

    // Assert
    TestTrue(TEXT("TryGet<float> should succeed"), bGot);
    TestEqual(TEXT("Value should be 2.5"), Value, 2.5f);
    
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TryGet_Bool,
    "Ledger.LedgerSubsystem.TryGet.Bool",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TryGet_Bool::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("HasStarted");

    Fixture.Subsystem->TrySet<bool>(Domain, Name, true);

    // Act
    bool Value = false;
    const bool bGot = Fixture.Subsystem->TryGet<bool>(Domain, Name, Value);

    // Assert
    TestTrue(TEXT("TryGet<bool> should succeed"), bGot);
    TestTrue(TEXT("Value should be true"), Value);
    
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLedgerSubsystem_TryGet_String,
    "Ledger.LedgerSubsystem.TryGet.String",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerSubsystem_TryGet_String::RunTest(const FString&)
{
    // Arrange
    const FLedgerSubsystemTestFixture Fixture;
    TestNotNull(TEXT("Subsystem should not be null"), Fixture.Subsystem);
    
    const FName Domain = TEXT("TestDomain");
    const FName Name = TEXT("Message");

    Fixture.Subsystem->TrySet<FString>(Domain, Name, TEXT("Test OK"));

    // Act
    FString Value;
    const bool bGot = Fixture.Subsystem->TryGet<FString>(Domain, Name, Value);

    // Assert
    TestTrue(TEXT("TryGet<FString> should succeed"), bGot);
    TestEqual(TEXT("Value should match"), Value, TEXT("Test OK"));
    
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
