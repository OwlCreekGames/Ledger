// Copyright Owl Creek Games. All Rights Reserved.

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "LedgerValue.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ConstructorDefaultTest,
	"Ledger.LedgerValue.Constructor.Default",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ConstructorDefaultTest::RunTest(const FString& Parameters)
{
	// Arrange & Act
	const FLedgerValue StateValue = FLedgerValue();

	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::Null);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ConstructorInt32Test,
	"Ledger.LedgerValue.Constructor.Int32",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ConstructorInt32Test::RunTest(const FString& Parameters)
{
	// Arrange & Act
	const FLedgerValue StateValue = FLedgerValue(1234567890);

	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::Int32);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ConstructorFloatTest,
	"Ledger.LedgerValue.Constructor.Float",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ConstructorFloatTest::RunTest(const FString& Parameters)
{
	// Arrange & Act
	const FLedgerValue StateValue = FLedgerValue(1.5f);

	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::Float);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ConstructorBoolTest,
	"Ledger.LedgerValue.Constructor.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ConstructorBoolTest::RunTest(const FString& Parameters)
{
	// Arrange & Act
	const FLedgerValue StateValue = FLedgerValue(true);

	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::Bool);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ConstructorStringTest,
	"Ledger.LedgerValue.Constructor.String",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ConstructorStringTest::RunTest(const FString& Parameters)
{
	// Arrange & Act
	const FLedgerValue StateValue = FLedgerValue(FString("Test String"));

	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::String);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_SetInt32Test,
	"Ledger.LedgerValue.Set.Int32",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_SetInt32Test::RunTest(const FString& Parameters)
{
	// Arrange
	FLedgerValue StateValue = FLedgerValue();

	// Act
	StateValue.Set(1234567890);
	
	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::Int32);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_SetFloatTest,
	"Ledger.LedgerValue.Set.Float",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_SetFloatTest::RunTest(const FString& Parameters)
{
	// Arrange
	FLedgerValue StateValue = FLedgerValue();

	// Act
	StateValue.Set(1.5f);
	
	// Assert
	TestEqual(TEXT("Type should be equalt"), StateValue.GetType(), ELedgerValueType::Float);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_SetBoolTest,
	"Ledger.LedgerValue.Set.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_SetBoolTest::RunTest(const FString& Parameters)
{
	// Arrange
	FLedgerValue StateValue = FLedgerValue();

	// Act
	StateValue.Set(true);
	
	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::Bool);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_SetStringTest,
	"Ledger.LedgerValue.Set.String",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_SetStringTest::RunTest(const FString& Parameters)
{
	// Arrange
	FLedgerValue StateValue = FLedgerValue();

	// Act
	StateValue.Set(FString("Test String"));
	
	// Assert
	TestEqual(TEXT("Type should be equal"), StateValue.GetType(), ELedgerValueType::String);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_TryGetInt32Test,
	"Ledger.LedgerValue.TryGet.Int32",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_TryGetInt32Test::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(1234567890);
	
	// Act
	int32 Value = 0;
	const bool Result = StateValue.TryGet(Value);

	// Assert
	TestTrue(TEXT("TryGet should return true"), Result);
	TestEqual(TEXT("Value should be equal"), Value, 1234567890);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_TryGetFloatTest,
	"Ledger.LedgerValue.TryGet.Float",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_TryGetFloatTest::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(1.5f);
	
	// Act
	float Value = 0.0f;
	const bool Result = StateValue.TryGet(Value);

	// Assert
	TestTrue(TEXT("TryGet should return true"), Result);
	TestEqual(TEXT("Value should be equal"), Value, 1.5f);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_TryGetBoolTest,
	"Ledger.LedgerValue.TryGet.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_TryGetBoolTest::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(true);
	
	// Act
	bool Value = false;
	const bool Result = StateValue.TryGet(Value);

	// Assert
	TestTrue(TEXT("TryGet should return true"), Result);
	TestEqual(TEXT("Value should be equal"), Value, true);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_TryGetStringTest,
	"Ledger.LedgerValue.TryGet.String",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_TryGetStringTest::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(FString("Test String"));
	
	// Act
	FString Value = FString();
	const bool Result = StateValue.TryGet(Value);

	// Assert
	TestTrue(TEXT("TryGet should return true"), Result);
	TestEqual(TEXT("Value should be equal"), Value, FString("Test String"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ToStringInt32Test,
	"Ledger.LedgerValue.ToString.Int32",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ToStringInt32Test::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(1234567890);
	
	// Act
	const FString Result = StateValue.ToString();

	// Assert
	TestEqual(TEXT("Value should be equal"), Result, TEXT("1234567890"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ToStringFloatTest,
	"Ledger.LedgerValue.ToString.Float",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ToStringFloatTest::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(1.5f);
	
	// Act
	const FString Result = StateValue.ToString();

	// Assert
	TestEqual(TEXT("Value should be equal"), Result, TEXT("1.5"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ToStringBoolTest,
	"Ledger.LedgerValue.ToString.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ToStringBoolTest::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(true);
	
	// Act
	const FString Result = StateValue.ToString();

	// Assert
	TestEqual(TEXT("Value should be equal"), Result, TEXT("true"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerValue_ToStringStringTest,
	"Ledger.LedgerValue.ToString.String",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerValue_ToStringStringTest::RunTest(const FString& Parameters)
{
	// Arrange
	const FLedgerValue StateValue = FLedgerValue(FString("Test String"));
	
	// Act
	const FString Result = StateValue.ToString();

	// Assert
	TestEqual(TEXT("Value should be equal"), Result, TEXT("Test String"));
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
