// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LedgerK2Node.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintInternalUseOnly)
class LEDGEREDITOR_API ULedgerK2Node : public UK2Node
{
	GENERATED_BODY()

public:
	
	//K2Node implementation
	virtual FText GetMenuCategory() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	//K2Node implementation
};
