// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerEditorPinFactory.h"
#include "GraphPin_LedgerDomainName.h"

class ULedgerTypedDomainK2Node_TryGetValue;

TSharedPtr<SGraphPin> FLedgerEditorPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	// if (InPin->GetOwningNode() && InPin->GetOwningNode()->IsA<ULedgerTypedDomainK2Node_TryGetValue>())
	// {
	// 	if (InPin->PinName == TEXT("Domain Name") && InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Name)
	// 	{
	// 		return SNew(SGraphPin_LedgerDomainName, InPin);
	// 	}
	// }

	return nullptr;
}
