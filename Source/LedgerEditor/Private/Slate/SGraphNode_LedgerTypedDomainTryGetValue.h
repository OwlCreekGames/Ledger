// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KismetNodes/SGraphNodeK2Base.h"

class SGraphNode_LedgerTypedDomainTryGetValue : public SGraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_LedgerTypedDomainTryGetValue) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UK2Node* InNode);

protected:
	virtual void CreatePinWidgets() override;

private:
	// Dropdown building
	TSharedRef<SWidget> MakeDomainSelector();
	void OnDomainChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo);
	TSharedRef<SWidget> OnGenerateDomainItem(TSharedPtr<FName> InItem) const;
	FText GetSelectedDomainText() const;

	// Dropdown data
	TArray<TSharedPtr<FName>> DomainNames;
	TSharedPtr<FName> SelectedDomain;
};