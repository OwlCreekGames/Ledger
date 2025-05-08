// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LedgerK2Node.h"
#include "UObject/Object.h"
#include "K2Node_LedgerTypedDomainTryGetValue.generated.h"

/**
 * 
 */
UCLASS()
class LEDGEREDITOR_API UK2Node_LedgerTypedDomainTryGetValue : public ULedgerK2Node
{
	GENERATED_BODY()

public:
	
	//UEdGraphNode implementation
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	//virtual FLinearColor GetNodeTitleColor() const override;
	//virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	//UEdGraphNode implementation

	//K2Node implementation
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	//K2Node implementation

	UPROPERTY(EditAnywhere, Category = "Domain")
	FName DomainName;
};
