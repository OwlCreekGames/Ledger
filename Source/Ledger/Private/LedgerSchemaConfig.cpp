// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerSchemaConfig.h"

#include "Misc/DataValidation.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "FLedgerModule"

inline EDataValidationResult ULedgerSchemaConfig::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	int EntryIndex = 0;

	for (const auto& Row : Entries->GetRowMap())
	{
		if (Row.Key.IsNone())
		{
			Result = EDataValidationResult::Invalid;
			Context.AddError(FText::Format(LOCTEXT("SchemaEntryNameIsNone", "Entry at index {0} has no name."), FText::AsNumber(EntryIndex)));
		}
		
		// if (const FLedgerSchemaRow* SchemaRow = reinterpret_cast<FLedgerSchemaRow*>(Row.Value))
		// {
		// }
		
		++EntryIndex;
	}
	
	return Result;
}

#endif