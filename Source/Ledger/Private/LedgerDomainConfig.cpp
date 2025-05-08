// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomainConfig.h"
#include "LedgerTypedDomain.h"
#include "Misc/DataValidation.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "FLedgerModule"

EDataValidationResult ULedgerDomainConfig::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	if (DomainName.IsNone())
	{
		Result = EDataValidationResult::Invalid;
		Context.AddError(LOCTEXT("DomainNameIsNone", "Domain asset is missing a name."));
	}
	
	if (!DomainClass)
	{
		Result = EDataValidationResult::Invalid;
		Context.AddError(LOCTEXT("DomainClassIsNone", "Domain asset has no class assigned."));
	}

	if (DomainClass && DomainClass->IsChildOf(ULedgerTypedDomain::StaticClass()) && !SchemaAsset)
	{
		Result = EDataValidationResult::Invalid;
		Context.AddError(FText::Format(LOCTEXT("DomainSchemaIsRequired", "Domain '{0}' uses a typed class but has no schema assigned."), FText::FromName(DomainName)));
	}
	
	return Result;
}

#undef LOCTEXT_NAMESPACE

#endif
