// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerEditorNodeFactory.h"
#include "LedgerTypedDomainK2Node_TryGetValue.h"
#include "GraphNode_LedgerTypedDomainNode.h"

TSharedPtr<SGraphNode> FLedgerEditorNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	// if (ULedgerTypedDomainK2Node_TryGetValue* TypedNode = Cast<ULedgerTypedDomainK2Node_TryGetValue>(Node))
	// {
	// 	return SNew(SGraphNode_LedgerTypedDomainNode, Node);
	// }

	return nullptr;
}
