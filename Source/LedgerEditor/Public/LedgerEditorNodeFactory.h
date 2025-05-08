// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "EdGraphUtilities.h"

class FLedgerEditorNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};
