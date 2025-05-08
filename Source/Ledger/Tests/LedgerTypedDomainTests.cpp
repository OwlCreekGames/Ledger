// Copyright Owl Creek Games. All Rights Reserved.

#if WITH_DEV_AUTOMATION_TESTS

#include "LedgerSchemaConfig.h"
#include "Misc/AutomationTest.h"
#include "LedgerTypedDomain.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_HasName_TrueForNameInSchema,
	"Ledger.LedgerTypedDomain.HasName.TrueForNameInSchema",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_HasName_TrueForNameInSchema::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("TestName");

	// Act
	const bool bHasName = Domain->HasName(Name);

	// Assert
	TestTrue(TEXT("HasName should return true for a name that is part of the schema."), bHasName);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_HasName_FalseForNameNotInSchema,
	"Ledger.LedgerTypedDomain.HasName.FalseForNameNotInSchema",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_HasName_FalseForNameNotInSchema::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("InvalidName");

	// Act
	const bool bHasName = Domain->HasName(Name);

	// Assert
	TestFalse(TEXT("HasName should return false for a name that is not part of the schema."), bHasName);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_GetNames,
	"Ledger.LedgerTypedDomain.GetNames",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_GetNames::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries->AddRow(FName("Name1"), Entry);
	
	Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries->AddRow(FName("Name2"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

	// Act
	const TArray<FName> Names = Domain->GetNames();

	// Assert
	TestEqual(TEXT("Should return 2 names"), Names.Num(), 2);
	TestTrue(TEXT("Should contain 'Name1'"), Names.Contains(TEXT("Name1")));
	TestTrue(TEXT("Should contain 'Name2'"), Names.Contains(TEXT("Name2")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TryGetValue_Int32_Default,
	"Ledger.LedgerTypedDomain.TryGetValue.Int32.Default",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TryGetValue_Int32_Default::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("TestName");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Name, OutValue);

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
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Float;
	Entry.DefaultFloat = 1.5f;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("TestName");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Name, OutValue);

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
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Bool;
	Entry.DefaultBool = true;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("TestName");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Name, OutValue);

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
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::String;
	Entry.DefaultString = TEXT("String Value");
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("TestName");

	// Act
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Name, OutValue);

	// Assert
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	FString StringValue;
	TestTrue(TEXT("Value should be retrievable as bool"), OutValue.TryGet(StringValue));
	TestEqual(TEXT("Retrieved value should match set value"), StringValue, TEXT("String Value"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TrySetValue_TrueForValidNameAndValue,
	"Ledger.LedgerTypedDomain.TrySetValue.TrueForValidNameAndValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TrySetValue_TrueForValidNameAndValue::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

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
	FLedgerTypedDomain_TrySetValue_FalseForIncorrectType,
	"Ledger.LedgerTypedDomain.TrySetValue.FalseForIncorrectType",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TrySetValue_FalseForIncorrectType::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

	const FName Name = TEXT("TestName");
	const FLedgerValue Value(1.5f);
	
	// Act
	const bool bSet = Domain->TrySetValue(Name, Value);

	// Assert
	TestFalse(TEXT("TrySetValue should return false"), bSet);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLedgerTypedDomain_TrySetValue_FalseForInvalidName,
	"Ledger.LedgerTypedDomain.TrySetValue.FalseForInvalidName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLedgerTypedDomain_TrySetValue_FalseForInvalidName::RunTest(const FString&)
{
	// Setup
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = 42;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);

	const FName Name = TEXT("InvalidName");
	const FLedgerValue Value(123);
	
	// Act
	const bool bSet = Domain->TrySetValue(Name, Value);

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
	ULedgerSchemaConfig* Schema = NewObject<ULedgerSchemaConfig>();
	Schema->Entries = NewObject<UDataTable>(Schema, TEXT("Entries"));
	Schema->Entries->RowStruct = FLedgerSchemaRow::StaticStruct();
	
	FLedgerSchemaRow Entry = FLedgerSchemaRow();
	Entry.Type = ELedgerValueType::Int32;
	Entry.DefaultInt32 = -1;
	Schema->Entries->AddRow(FName("TestName"), Entry);
	
	ULedgerTypedDomain* Domain = NewObject<ULedgerTypedDomain>();
	Domain->InitializeFromSchema(Schema);
	
	const FName Name = TEXT("TestName");
	FLedgerValue Value(42);
	
	// Act
	const bool bSet = Domain->TrySetValue(Name, Value);
	
	FLedgerValue OutValue;
	const bool bGet = Domain->TryGetValue(Name, OutValue);

	// Assert
	TestTrue(TEXT("TrySetValue should return true"), bSet);
	TestTrue(TEXT("TryGetValue should return true"), bGet);
	int32 IntValue;
	TestTrue(TEXT("Value should be retrievable as int32"), OutValue.TryGet(IntValue));
	TestEqual(TEXT("Retrieved value should match set value"), IntValue, 42);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
