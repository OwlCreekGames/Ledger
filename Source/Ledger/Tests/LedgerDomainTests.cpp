// Copyright Owl Creek Games. All Rights Reserved.

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "LedgerDomain.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_HasKey_TrueAfterSet,
	"Ledger.LedgerDomain.HasKey.TrueAfterSet",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_HasKey_TrueAfterSet::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Key = TEXT("TestKey");
	Domain->TrySet<int32>(Key, 123);

	// Act
	const bool bHasKey = Domain->HasKey(Key);

	// Assert
	TestTrue(TEXT("HasKey should return true for a key that was set"), bHasKey);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_HasKey_FalseForUnsetKey,
	"Ledger.LedgerDomain.HasKey.FalseForUnsetKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_HasKey_FalseForUnsetKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	const bool bHasKey = Domain->HasKey(TEXT("InvalidKey"));

	// Assert
	TestFalse(TEXT("HasKey should return false for a key that was never set"), bHasKey);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_HasKey_EmptyName,
	"Ledger.LedgerDomain.HasKey.EmptyKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_HasKey_EmptyName::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName EmptyKey = NAME_None;

	// Act & Assert
	const bool bHasKey = Domain->HasKey(EmptyKey);
	TestFalse(TEXT("HasKey should return false for NAME_None"), bHasKey);

	// Act & Assert
	Domain->TrySet<int32>(EmptyKey, 1);
	TestTrue(TEXT("HasKey should return true after explicitly setting NAME_None"), Domain->HasKey(EmptyKey));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_GetKeys,
	"Ledger.LedgerDomain.GetKeys",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_GetKeys::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	Domain->TrySet<int32>(TEXT("Key1"), 1);
	Domain->TrySet<int32>(TEXT("Key2"), 2);

	// Act
	const TArray<FName> Keys = Domain->GetKeys();

	// Assert
	TestEqual(TEXT("Should return 2 keys"), Keys.Num(), 2);
	TestTrue(TEXT("Should contain 'Key1'"), Keys.Contains(TEXT("Key1")));
	TestTrue(TEXT("Should contain 'Key2'"), Keys.Contains(TEXT("Key2")));

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
	
	const FName Key = TEXT("TestKey");
	const FLedgerValue Value(123);

	// Act
	const bool bSet = Domain->TrySetValue(Key, Value);

	// Assert
	TestTrue(TEXT("TrySetValue should return true"), bSet);
	TestTrue(TEXT("HasKey should return true for a key that was set"), Domain->HasKey(Key));

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
	
	const FName Key = TEXT("TestKey");

	// Act
	const bool bSet = Domain->TrySet<int32>(Key, 123);

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasKey should return true for a key that was set"), Domain->HasKey(Key));

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
	
	const FName Key = TEXT("TestKey");

	// Act
	const bool bSet = Domain->TrySet<float>(Key, 1.5f);

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasKey should return true for a key that was set"), Domain->HasKey(Key));

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
	
	const FName Key = TEXT("TestKey");

	// Act
	const bool bSet = Domain->TrySet<bool>(Key, true);

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasKey should return true for a key that was set"), Domain->HasKey(Key));

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
	
	const FName Key = TEXT("TestKey");

	// Act
	const bool bSet = Domain->TrySet<FString>(Key, FString("Test String"));

	// Assert
	TestTrue(TEXT("TrySet should return true"), bSet);
	TestTrue(TEXT("HasKey should return true for a key that was set"), Domain->HasKey(Key));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGetValue,
	"Ledger.LedgerDomain.TryGetValue.ValidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGetValue::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Key = TEXT("TestKey");
	const FLedgerValue Value(123);
	Domain->TrySetValue(Key, Value);

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	int32 IntValue;
	TestTrue(TEXT("Value should be retrievable as int32"), OutValue.TryGet(IntValue));
	TestEqual(TEXT("Retrieved value should match set value"), IntValue, 123);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Int32,
	"Ledger.LedgerDomain.TryGet.Int32.ValidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Int32::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Key = TEXT("TestKey");
	Domain->TrySet<int32>(Key, 123);

	// Act
	int32 OutValue;
	const bool bGet = Domain->TryGet<int32>(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestEqual(TEXT("Retrieved value should match set value"), OutValue, 123);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Float,
	"Ledger.LedgerDomain.TryGet.Float.ValidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Float::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Key = TEXT("TestKey");
	Domain->TrySet<float>(Key, 1.5f);

	// Act
	float OutValue;
	const bool bGet = Domain->TryGet<float>(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestEqual(TEXT("Retrieved value should match set value"), OutValue, 1.5f);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Bool,
	"Ledger.LedgerDomain.TryGet.Bool.ValidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Bool::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Key = TEXT("TestKey");
	Domain->TrySet<bool>(Key, true);

	// Act
	bool OutValue;
	const bool bGet = Domain->TryGet<bool>(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestTrue(TEXT("Retrieved value should match set value"), OutValue);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_String,
	"Ledger.LedgerDomain.TryGet.String.ValidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_String::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	const FName Key = TEXT("TestKey");
	Domain->TrySet<FString>(Key, FString("Test String"));

	// Act
	FString OutValue;
	const bool bGet = Domain->TryGet<FString>(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGet should return true"), bGet);
	TestEqual(TEXT("Retrieved value should match set value"), OutValue, FString("Test String"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGetValue_InvalidKey,
	"Ledger.LedgerDomain.TryGetValue.InvalidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGetValue_InvalidKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(TEXT("InvalidKey"), OutValue);

	// Assert
	TestFalse(TEXT("TryGetValue should return false for non-existent key"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Int32_InvalidKey,
	"Ledger.LedgerDomain.TryGet.Int32.InvalidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Int32_InvalidKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	int32 OutValue;
	const bool bGet = Domain->TryGet<int32>(TEXT("InvalidKey"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent key"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Float_InvalidKey,
	"Ledger.LedgerDomain.TryGet.Float.InvalidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Float_InvalidKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	float OutValue;
	const bool bGet = Domain->TryGet<float>(TEXT("InvalidKey"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent key"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_Bool_InvalidKey,
	"Ledger.LedgerDomain.TryGet.Bool.InvalidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_Bool_InvalidKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	bool OutValue;
	const bool bGet = Domain->TryGet<bool>(TEXT("InvalidKey"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent key"), bGet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerDomain_TryGet_String_InvalidKey,
	"Ledger.LedgerDomain.TryGet.String.InvalidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerDomain_TryGet_String_InvalidKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomain* Domain = NewObject<ULedgerDomain>();
	TestNotNull(TEXT("Domain should be valid"), Domain);
	
	// Act
	FString OutValue;
	const bool bGet = Domain->TryGet<FString>(TEXT("InvalidKey"), OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for non-existent key"), bGet);

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
	
	const FName Key = TEXT("TestKey");
	Domain->TrySet<FString>(Key, TEXT("Not An Integer"));

	// Act
	int32 OutValue;
	const bool bGet = Domain->TryGet<int32>(Key, OutValue);

	// Assert
	TestFalse(TEXT("TryGet should return false for type mismatch"), bGet);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
