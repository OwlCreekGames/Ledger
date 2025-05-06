// Copyright Epic Games, Inc. All Rights Reserved.
// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FLedgerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
