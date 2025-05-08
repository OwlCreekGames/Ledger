// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "SGraphPin.h"

class SGraphPin_LedgerDomainName : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGraphPin_LedgerDomainName) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

protected:
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;

private:
	TArray<TSharedPtr<FName>> DomainNames;
	TSharedPtr<FName> SelectedName;

	void OnSelectionChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo);
	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FName> InItem) const;
	FText GetSelectedText() const;

	void LoadDomainNames();
};

