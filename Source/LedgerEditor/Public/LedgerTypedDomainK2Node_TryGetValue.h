// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

/*
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LedgerTypedDomainK2Node_TryGetValue.generated.h"

UCLASS(Category = "Ledger")
class LEDGEREDITOR_API ULedgerTypedDomainK2Node_TryGetValue : public UK2Node
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	
	virtual FText GetMenuCategory() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	
	UPROPERTY(EditAnywhere, Category = "Domain")
	FName DomainName;
	
private:
	//void UpdateNameOptions(FName SelectedDomain);
	void TryGetMenuEntriesForDomainName(const UEdGraphPin* Pin, TArray<FString>& OutMenuOptions) const;
};
*/