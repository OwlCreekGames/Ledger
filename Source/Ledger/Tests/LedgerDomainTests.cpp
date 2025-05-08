// Copyright Owl Creek Games. All Rights Reserved.

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "LedgerDomain.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_HasName_TrueAfterSet,
	"Ledger.LedgerDomain.HasName.TrueAfterSet",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_HasName_TrueAfterSet::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	Domain->TrySet<int32>(Name, 123);

	// Act
	const bool bHasName = Domain->HasName(Name);

	// Assert
	TestTrue(TEXT("HasName should return true for a name that was set"), bHasName);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_HasName_FalseForUnsetName,
	"Ledger.LedgerDomain.HasName.FalseForUnsetName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_HasName_FalseForUnsetName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	const bool bHasName = Domain->HasName(TEXT("InvalidName"));

	// Assert
	TestFalse(TEXT("HasName should return false for a name that was never set"), bHasName);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_HasName_EmptyName,
	"Ledger.LedgerDomain.HasName.EmptyName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_HasName_EmptyName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName EmptyName = NAME_None;

	// Act & Assert
	const bool bHasName = Domain->HasName(EmptyName);
	TestFalse(TEXT("HasName should return false for NAME_None"), bHasName);

	// Act & Assert
	Domain->TrySet<int32>(EmptyName, 1);
	TestTrue(TEXT("HasName should return true after explicitly setting NAME_None"), Domain->HasName(EmptyName));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_GetNames,
	"Ledger.LedgerDomain.GetNames",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_GetNames::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	Domain->TrySet<int32>(TEXT("Name1"), 1);
	Domain->TrySet<int32>(TEXT("Name2"), 2);

	// Act
	const TArray<FName> Names = Domain->GetNames();

	// Assert
	TestEqual(TEXT("Should return 2 names"), Names.Num(), 2);
	TestTrue(TEXT("Should contain 'Name1'"), Names.Contains(TEXT("Name1")));
	TestTrue(TEXT("Should contain 'Name2'"), Names.Contains(TEXT("Name2")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TrySetValue,
	"Ledger.LedgerDomain.TrySetValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TrySetValue::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	const FLedgerValue Value(123);

	// Act
	const bool bSet = Domain->TrySetValue(Name, Value);

	// Assert
	TestTrue(TEXT("TrySetValue should return true"), bSet);
	TestTrue(TEXT("HasName should return true for a name that was set"), Domain->HasName(Name));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TrySet_Int32,
	"Ledger.LedgerDomain.TrySet.Int32",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TrySet_Int32::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");

	// Act
	const bool bSet = Domain->TrySet<int32>(Name, 123);

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasName should return true for a name that was set"), Domain->HasName(Name));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TrySet_Float,
	"Ledger.LedgerDomain.TrySet.Float",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TrySet_Float::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");

	// Act
	const bool bSet = Domain->TrySet<float>(Name, 1.5f);

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasName should return true for a name that was set"), Domain->HasName(Name));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TrySet_Bool,
	"Ledger.LedgerDomain.TrySet.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TrySet_Bool::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");

	// Act
	const bool bSet = Domain->TrySet<bool>(Name, true);

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasName should return true for a name that was set"), Domain->HasName(Name));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TrySet_String,
	"Ledger.LedgerDomain.TrySet.String",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TrySet_String::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");

	// Act
	const bool bSet = Domain->TrySet<FString>(Name, FString("Test String"));

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasName should return true for a name that was set"), Domain->HasName(Name));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGetValue,
	"Ledger.LedgerDomain.TryGetValue.ValidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGetValue::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	const FLedgerValue Value(123);
	Domain->TrySetValue(Name, Value);

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Name, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	int32 IntValue;
	TestTrue(TEXT("Value should be retrievable as int32"), OutValue.TryGet(IntValue));
	TestEqual(TEXT("Retrieved value should match set value"), IntValue, 123);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Int32,
	"Ledger.LedgerDomain.TryGet.Int32.ValidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Int32::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	Domain->TrySet<int32>(Name, 123);

	// Act
	int32 OutValue;
	const bool bGet = Domain->TryGet<int32>(Name, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestEqual(TEXT("Retrieved value should match set value"), OutValue, 123);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Float,
	"Ledger.LedgerDomain.TryGet.Float.ValidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Float::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	Domain->TrySet<float>(Name, 1.5f);

	// Act
	float OutValue;
	const bool bGet = Domain->TryGet<float>(Name, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestEqual(TEXT("Retrieved value should match set value"), OutValue, 1.5f);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Bool,
	"Ledger.LedgerDomain.TryGet.Bool.ValidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Bool::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	Domain->TrySet<bool>(Name, true);

	// Act
	bool OutValue;
	const bool bGet = Domain->TryGet<bool>(Name, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestTrue(TEXT("Retrieved value should match set value"), OutValue);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_String,
	"Ledger.LedgerDomain.TryGet.String.ValidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_String::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	Domain->TrySet<FString>(Name, FString("Test String"));

	// Act
	FString OutValue;
	const bool bGet = Domain->TryGet<FString>(Name, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestEqual(TEXT("Retrieved value should match set value"), OutValue, FString("Test String"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGetValue_InvalidName,
	"Ledger.LedgerDomain.TryGetValue.InvalidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGetValue_InvalidName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(TEXT("InvalidName"), OutValue);

	// Assert
	TestFalse(TEXT("TryGetValue should return false for non-existent name"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Int32_InvalidName,
	"Ledger.LedgerDomain.TryGet.Int32.InvalidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Int32_InvalidName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	int32 OutValue;
	const bool bGet = Domain->TryGet<int32>(TEXT("InvalidName"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent name"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Float_InvalidName,
	"Ledger.LedgerDomain.TryGet.Float.InvalidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Float_InvalidName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	float OutValue;
	const bool bGet = Domain->TryGet<float>(TEXT("InvalidName"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent name"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Bool_InvalidName,
	"Ledger.LedgerDomain.TryGet.Bool.InvalidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Bool_InvalidName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	bool OutValue;
	const bool bGet = Domain->TryGet<bool>(TEXT("InvalidName"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent name"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_String_InvalidName,
	"Ledger.LedgerDomain.TryGet.String.InvalidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_String_InvalidName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	FString OutValue;
	const bool bGet = Domain->TryGet<FString>(TEXT("InvalidName"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent name"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_TypeMismatch,
	"Ledger.LedgerDomain.TryGet.TypeMismatch",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_TypeMismatch::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Name = TEXT("TestName");
	Domain->TrySet<FString>(Name, TEXT("Not An Integer"));

	// Act
	int32 OutValue;
	const bool bGet = Domain->TryGet<int32>(Name, OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for type mismatch"), bGet);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
