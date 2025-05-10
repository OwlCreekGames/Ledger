// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerTypedDomain.h"

#include "LedgerDomainConfig.h"
#include "LedgerSchemaConfig.h"

void ULedgerTypedDomain::InitializeFromSchema(ULedgerSchemaConfig* InSchema)
{
	
	if (!InSchema)
	{
		const FName DomainName = DomainConfig ? DomainConfig->DomainName : TEXT("<Unknown Domain Name>");
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Schema is NULL; skipping InitializeFromSchema. Domain '%s' will be unusable."), *DomainName.ToString());
		return;
	}
	
	Schema = InSchema;
	
	InitializeSchemaLookupMap();
	InitializeDefaultValues();
}

bool ULedgerTypedDomain::TrySetValue(const FName Name, const FLedgerValue& Value)
{
	const FLedgerSchemaItem** Entry = SchemaLookupMap.Find(Name);
	if (!Entry)
	{
		UE_LOG(LogLedger, Warning,	TEXT("Name '%s' not found in domain schema."), *Name.ToString());
		return false;
	}

	if (Value.GetType() != (*Entry)->Type)
	{
		UE_LOG(
			LogLedger,
			Warning,
			TEXT("Value type '%s' does not match schema type '%s' for name '%s'."),
			*UEnum::GetValueAsString(Value.GetType()),
			*UEnum::GetValueAsString((*Entry)->Type),
			*Name.ToString());
		
		return false;
	}
	
	return Super::TrySetValue(Name, Value);
}

void ULedgerTypedDomain::InitializeSchemaLookupMap()
{
	SchemaLookupMap.Empty();

	if (Schema->Items.Num() == 0)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Schema '%s' has no entries."), *Schema->GetName());
		return;
	}
	
	for (const FLedgerSchemaItem& Entry : Schema->Items)
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
	
	for (const FLedgerSchemaItem& Entry : Schema->Items)
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