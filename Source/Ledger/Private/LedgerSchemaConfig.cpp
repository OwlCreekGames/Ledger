// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerSchemaConfig.h"

#include "Misc/DataValidation.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "FLedgerModule"

inline EDataValidationResult ULedgerSchemaConfig::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	TArray<FName> Names;
	int EntryIndex = 0;
	
	for (const FLedgerSchemaItem& Entry : Items)
	{
		if (Entry.Name.IsNone())
		{
			Result = EDataValidationResult::Invalid;
			Context.AddError(FText::Format(LOCTEXT("Ledger.SchemaEntryNameIsNone", "Entry at index {0} has no name."), FText::AsNumber(EntryIndex)));
		}

		if (Names.Contains(Entry.Name))
		{
			Result = EDataValidationResult::Invalid;
			Context.AddError(FText::Format(LOCTEXT("Ledger.SchemaEntryNameIsDuplicate", "Entry at index {0} has a duplicate name."), FText::AsNumber(EntryIndex)));
		}
		
		Names.Add(Entry.Name);

		++EntryIndex;
	}

	return Result;
}

#endif