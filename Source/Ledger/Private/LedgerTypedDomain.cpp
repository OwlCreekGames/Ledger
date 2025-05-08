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
	uint8* const* RowPtr = SchemaRowMap.Find(Name);
	if (!RowPtr)
	{
		UE_LOG(LogLedger, Warning,	TEXT("Name '%s' not found in domain schema."), *Name.ToString());
		return false;
	}
	
	const FLedgerSchemaRow* Row = reinterpret_cast<const FLedgerSchemaRow*>(*RowPtr);
	
	if (Value.GetType() != Row->Type)
	{
		UE_LOG(
			LogLedger,
			Warning,
			TEXT("Value type '%s' does not match schema type '%s' for name '%s'."),
			*UEnum::GetValueAsString(Value.GetType()),
			*UEnum::GetValueAsString(Row->Type),
			*Name.ToString());
		
		return false;
	}
	
	return Super::TrySetValue(Name, Value);
}

void ULedgerTypedDomain::InitializeSchemaLookupMap()
{
	SchemaRowMap = Schema->Entries->GetRowMap();

	if (SchemaRowMap.Num() == 0)
	{
		UE_LOG(LogLedger, Warning, TEXT("Ledger: Schema '%s' has no entries."), *Schema->GetName());
	}
}

void ULedgerTypedDomain::InitializeDefaultValues()
{
	if (Schema == nullptr)
	{
		return;
	}

	for (const auto& Row : SchemaRowMap)
	{
		if (const FLedgerSchemaRow* Entry = reinterpret_cast<FLedgerSchemaRow*>(Row.Value))
		{
			switch (Entry->Type)
			{
				case ELedgerValueType::Int32:
					TrySetValue(Row.Key, FLedgerValue(Entry->DefaultInt32));
					break;
						
				case ELedgerValueType::Float:
					TrySetValue(Row.Key, FLedgerValue(Entry->DefaultFloat));
					break;
						
				case ELedgerValueType::Bool:
					TrySetValue(Row.Key, FLedgerValue(Entry->DefaultBool));
					break;
						
				case ELedgerValueType::String:
					TrySetValue(Row.Key, FLedgerValue(Entry->DefaultString));
					break;
				default:
					checkf(false, TEXT("FATAL: Unsupported type in ULedgerTypedDomain::InitializeFromSchema!"));
			}
		}
	}
}