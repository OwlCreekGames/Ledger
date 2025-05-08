// Copyright Owl Creek Games. All Rights Reserved.


#include "Nodes/LedgerK2Node.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

FText ULedgerK2Node::GetMenuCategory() const
{
	return NSLOCTEXT("K2Node", "LedgerCategory", "Ledger");
}

void ULedgerK2Node::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	const UClass* Action = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}
