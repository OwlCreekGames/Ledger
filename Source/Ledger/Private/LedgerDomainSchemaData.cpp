// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomainSchemaData.h"

#include "Misc/DataValidation.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "FLedgerModule"

inline EDataValidationResult ULedgerDomainSchemaData::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	int EntryIndex = 0;
	for (const FLedgerDomainSchemaEntry& Entry : Entries)
	{
		if (Entry.Name.IsNone())
		{
			Result = EDataValidationResult::Invalid;
			Context.AddError(FText::Format(LOCTEXT("SchemaEntryNameIsNone", "Entry at index {0} has no name."), FText::AsNumber(EntryIndex)));
		}

		++EntryIndex;
	}

	return Result;
}

#endif