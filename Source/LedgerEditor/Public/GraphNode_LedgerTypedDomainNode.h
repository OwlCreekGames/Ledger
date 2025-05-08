// Copyright Owl Creek Games. All Rights Reserved.

#pragma once
/*
#include "KismetNodes/SGraphNodeK2Base.h"

class SGraphNode_LedgerTypedDomainNode : public SGraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_LedgerTypedDomainNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphNode* InNode);

protected:
	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	virtual TSharedRef<SWidget> CreateNodeContentAreaInternal();
private:
	// Dropdown building
	TSharedRef<SWidget> MakeDomainSelector();
	void OnDomainChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo);
	TSharedRef<SWidget> OnGenerateDomainItem(TSharedPtr<FName> InItem) const;
	FText GetSelectedDomainText() const;

	// Dropdown data
	TArray<TSharedPtr<FName>> DomainNames;
	TSharedPtr<FName> SelectedDomain;

	// Slot references
	// TSharedPtr<SVerticalBox> LeftNodeBox;
	// TSharedPtr<SVerticalBox> RightNodeBox;
};
*/
