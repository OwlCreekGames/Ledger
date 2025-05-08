// Copyright Owl Creek Games. All Rights Reserved.

/*
#include "LedgerTypedDomainK2Node_TryGetValue.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "K2Node_IfThenElse.h"
#include "KismetCompiler.h"
#include "LedgerSubsystem.h"

class UK2Node_IfThenElse;

void ULedgerTypedDomainK2Node_TryGetValue::AllocateDefaultPins()
{
	// Exec input
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, NAME_None, nullptr, TEXT("In"));

	// Inputs
	// CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Name, NAME_None, nullptr, TEXT("Domain Name"));
	// CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Name, NAME_None, nullptr, TEXT("Value Name"));

	// Exec outputs
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NAME_None, nullptr, TEXT("Success"));
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NAME_None, nullptr, TEXT("Failed"));

	// Value output
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_String, NAME_None, nullptr, TEXT("Value"));
}

void ULedgerTypedDomainK2Node_TryGetValue::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	//
	// // Locate the subsystem call
	// const FName FunctionName = GET_FUNCTION_NAME_CHECKED(ULedgerSubsystem, TryGetValue);
	//
	// UK2Node_CallFunction* CallNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	// CallNode->SetFromFunction(ULedgerSubsystem::StaticClass()->FindFunctionByName(FunctionName));
	// CallNode->AllocateDefaultPins();
	//
	// // Move pins
	// CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Domain Name")), *CallNode->FindPin(TEXT("Domain Name")));
	// CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Value Name")), *CallNode->FindPin(TEXT("Value Name")));
	//
	// // Temp var for return value (bool)
	// UEdGraphPin* BoolReturnPin = CallNode->GetReturnValuePin();
	//
	// // Create branching
	// UK2Node_IfThenElse* BranchNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
	// BranchNode->AllocateDefaultPins();
	//
	// CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *BranchNode->GetExecPin());
	// CompilerContext.MovePinLinksToIntermediate(*BoolReturnPin, *BranchNode->GetConditionPin());
	//
	// // Route success/failure
	// CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Success")), *BranchNode->GetThenPin());
	// CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Failed")), *BranchNode->GetElsePin());
	//
	// // Move value output
	// CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Value")), *CallNode->FindPin(TEXT("OutValue")));
	//
	// // Done
	// BreakAllNodeLinks();
}

void ULedgerTypedDomainK2Node_TryGetValue::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		ActionRegistrar.AddBlueprintAction(ActionKey, Spawner);
	}
}

FText ULedgerTypedDomainK2Node_TryGetValue::GetMenuCategory() const
{
	return NSLOCTEXT("K2Node", "LedgerCategory", "Ledger");
}

FText ULedgerTypedDomainK2Node_TryGetValue::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::Format(NSLOCTEXT("K2Node", "TryGetValueTitle", "Try Get Value\nDomain: {0}"), FText::FromName(DomainName));
}
*/

/*

FText ULedgerTypedDomainK2Node_TryGetValue::GetTooltipText() const
{
	return NSLOCTEXT("K2Node", "TryGetValueTooltip", "Attempts to retrieve a value for the selected domain.");
}

FSlateIcon ULedgerTypedDomainK2Node_TryGetValue::GetIconAndTint(FLinearColor& OutColor) const
{
	//static FSlateIcon Icon("EditorStyle", "GraphEditor.Function_16x");
	//return Icon;
	
	return Super::GetIconAndTint(OutColor);
}
*/