// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "EdGraphUtilities.h"

class FLedgerEditorPinFactory : public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
};
