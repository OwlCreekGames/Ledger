// Copyright Owl Creek Games. All Rights Reserved.

#if WITH_DEV_AUTOMATION_TESTS

#include "LedgerDomainSchemaData.h"
#include "Misc/AutomationTest.h"
#include "LedgerTypedDomain.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_HasKey_TrueForKeyInSchema,
	"Ledger.LedgerTypedDomain.HasKey.TrueForKeyInSchema",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_HasKey_TrueForKeyInSchema::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();

	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("TestKey");

	// Act
	const bool bHasKey = Domain->HasKey(Key);

	// Assert
	TestTrue(TEXT("HasKey should return true for a key that is part of the schema."), bHasKey);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_HasKey_FalseForKeyNotInSchema,
	"Ledger.LedgerTypedDomain.HasKey.FalseForKeyNotInSchema",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_HasKey_FalseForKeyNotInSchema::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();

	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("InvalidKey");

	// Act
	const bool bHasKey = Domain->HasKey(Key);

	// Assert
	TestFalse(TEXT("HasKey should return false for a key that is not part of the schema."), bHasKey);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_GetKeys,
	"Ledger.LedgerTypedDomain.GetKeys",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_GetKeys::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();

	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("Key1");
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries.Add(Entry);
	
	Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("Key2");
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

	// Act
	const TArray<FName> Keys = Domain->GetKeys();

	// Assert
	TestEqual(TEXT("Should return 2 keys"), Keys.Num(), 2);
	TestTrue(TEXT("Should contain 'Key1'"), Keys.Contains(TEXT("Key1")));
	TestTrue(TEXT("Should contain 'Key2'"), Keys.Contains(TEXT("Key2")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TryGetValue_Int32_Default,
	"Ledger.LedgerTypedDomain.TryGetValue.Int32.Default",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TryGetValue_Int32_Default::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();
	
	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = TEXT("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("TestKey");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	int32 IntValue;
	TestTrue(TEXT("Value should be retrievable as int32"), OutValue.TryGet(IntValue));
	TestEqual(TEXT("Retrieved value should match set value"), IntValue, 42);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TryGetValue_Float_Default,
	"Ledger.LedgerTypedDomain.TryGetValue.Float.Default",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TryGetValue_Float_Default::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();
	
	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Float;
	Entry.DefaultFloat = 1.5f;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("TestKey");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	float FloatValue;
	TestTrue(TEXT("Value should be retrievable as float"), OutValue.TryGet(FloatValue));
	TestEqual(TEXT("Retrieved value should match set value"), FloatValue, 1.5f);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TryGetValue_Bool_Default,
	"Ledger.LedgerTypedDomain.TryGetValue.Bool.Default",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TryGetValue_Bool_Default::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();
	
	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = TEXT("TestKey");
	Entry.Type = ELedgerValueType::Bool;
	Entry.DefaultBool = true;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("TestKey");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	bool BoolValue;
	TestTrue(TEXT("Value should be retrievable as bool"), OutValue.TryGet(BoolValue));
	TestEqual(TEXT("Retrieved value should match set value"), BoolValue, true);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TryGetValue_String_Default,
	"Ledger.LedgerTypedDomain.TryGetValue.String.Default",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TryGetValue_String_Default::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();
	
	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::String;
	Entry.DefaultString = TEXT("String Value");
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("TestKey");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Key, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	FString StringValue;
	TestTrue(TEXT("Value should be retrievable as bool"), OutValue.TryGet(StringValue));
	TestEqual(TEXT("Retrieved value should match set value"), StringValue, TEXT("String Value"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TrySetValue_TrueForValidKeyAndValue,
	"Ledger.LedgerTypedDomain.TrySetValue.TrueForValidKeyAndValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TrySetValue_TrueForValidKeyAndValue::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();

	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

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
	FLedgerTypedDomain_TrySetValue_FalseForIncorrectType,
	"Ledger.LedgerTypedDomain.TrySetValue.FalseForIncorrectType",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TrySetValue_FalseForIncorrectType::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();

	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

	const FName Key = TEXT("TestKey");
	const FLedgerValue Value(1.5f);
	
	// Act
	const bool bSet = Domain->TrySetValue(Key, Value);

	// Assert
	TestFalse(TEXT("TrySetValue should return false"), bSet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TrySetValue_FalseForInvalidKey,
	"Ledger.LedgerTypedDomain.TrySetValue.FalseForInvalidKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TrySetValue_FalseForInvalidKey::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();

	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

	const FName Key = TEXT("InvalidKey");
	const FLedgerValue Value(123);
	
	// Act
	const bool bSet = Domain->TrySetValue(Key, Value);

	// Assert
	TestFalse(TEXT("TrySetValue should return false"), bSet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TryGetValue_Update,
	"Ledger.LedgerTypedDomain.TryGetValue.Update",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TryGetValue_Update::RunTest(const FString&)
{
	// Setup
	ULedgerDomainSchemaData* Schema = NewObject<ULedgerDomainSchemaData>();
	
	FLedgerDomainSchemaEntry Entry = FLedgerDomainSchemaEntry();
	Entry.Name = FName("TestKey");
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = -1;
	Schema->Entries.Add(Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Key = TEXT("TestKey");
	FLedgerValue Value(42);
	
	// Act
	const bool bSet = Domain->TrySetValue(Key, Value);
	
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Key, OutValue);

	// Assert
	TestTrue(TEXT("TrySetValue should return true"), bSet);
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	int32 IntValue;
	TestTrue(TEXT("Value should be retrievable as int32"), OutValue.TryGet(IntValue));
	TestEqual(TEXT("Retrieved value should match set value"), IntValue, 42);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
