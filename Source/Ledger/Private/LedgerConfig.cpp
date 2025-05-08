// Copyright Owl Creek Games. All Rights Reserved.


#include "LedgerConfig.h"
#include "LedgerDomainConfig.h"
#include "Internationalization/Internationalization.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "FLedgerModule"

EDataValidationResult ULedgerConfig::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	int32 EntryIndex = 0;
	for (const TObjectPtr<ULedgerDomainConfig>& DomainAsset : Domains)
	{
		if (DomainAsset)
		{
			const EDataValidationResult ChildResult = DomainAsset->IsDataValid(Context);
			Result = CombineDataValidationResults(Result, ChildResult);
		} else
		{
			Result = EDataValidationResult::Invalid;
			Context.AddError(FText::Format(LOCTEXT("DomainEntryIsNull", "Null entry at index {0} in Domains"), FText::AsNumber(EntryIndex)));
		}

		++EntryIndex;
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE

#endif