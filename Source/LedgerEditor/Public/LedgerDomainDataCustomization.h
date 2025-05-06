﻿// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "IDetailCustomization.h"

class FLedgerDomainDataCustomization final : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};
