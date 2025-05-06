// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerTypedDomain.h"

#include "LedgerDomainSchemaData.h"

void ULedgerTypedDomain::InitializeFromSchema(ULedgerDomainSchemaData* InSchema)
{
	Schema = InSchema;
	
	InitializeSchemaLookupMap();
	InitializeDefaultValues();
}

bool ULedgerTypedDomain::TrySetValue(const FName Key, const FLedgerValue& Value)
{
	const FLedgerDomainSchemaEntry** Entry = SchemaLookupMap.Find(Key);
	if (!Entry)
	{
		UE_LOG(LogLedger, Warning,	TEXT("Key '%s' not found in domain schema."), *Key.ToString());
		return false;
	}

	if (Value.GetType() != (*Entry)->Type)
	{
		UE_LOG(
			LogLedger,
			Warning,
			TEXT("Value type '%s' does not match schema type '%s' for key '%s'."),
			*UEnum::GetValueAsString(Value.GetType()),
			*UEnum::GetValueAsString((*Entry)->Type),
			*Key.ToString());
		
		return false;
	}
	
	return Super::TrySetValue(Key, Value);
}

void ULedgerTypedDomain::InitializeSchemaLookupMap()
{
	SchemaLookupMap.Empty();
	
	if (Schema == nullptr)
	{
		return;
	}
	
	for (const FLedgerDomainSchemaEntry& Entry : Schema->Entries)
	{
		SchemaLookupMap.Add(Entry.Name, &Entry);
	}
}

void ULedgerTypedDomain::InitializeDefaultValues()
{
	if (Schema == nullptr)
	{
		return;
	}
	
	for (const FLedgerDomainSchemaEntry& Entry : Schema->Entries)
	{
		switch (Entry.Type)
		{
		case ELedgerValueType::Int32:
			TrySetValue(Entry.Name, FLedgerValue(Entry.DefaultInt32));
			break;
				
		case ELedgerValueType::Float:
			TrySetValue(Entry.Name, FLedgerValue(Entry.DefaultFloat));
			break;
				
		case ELedgerValueType::Bool:
			TrySetValue(Entry.Name, FLedgerValue(Entry.DefaultBool));
			break;
				
		case ELedgerValueType::String:
			TrySetValue(Entry.Name, FLedgerValue(Entry.DefaultString));
			break;
		default:
			checkf(false, TEXT("FATAL: Unsupported type in ULedgerTypedDomain::InitializeFromSchema!"));
		}
	}
}