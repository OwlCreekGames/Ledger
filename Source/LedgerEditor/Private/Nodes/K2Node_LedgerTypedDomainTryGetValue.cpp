// Copyright Owl Creek Games. All Rights Reserved.


#include "Nodes/K2Node_LedgerTypedDomainTryGetValue.h"
#include "K2Node_CallFunction.h"
#include "K2Node_IfThenElse.h"
#include "KismetCompiler.h"
#include "LedgerSubsystem.h"
#include "Slate/SGraphNode_LedgerTypedDomainTryGetValue.h"

void UK2Node_LedgerTypedDomainTryGetValue::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	
	
	check(Pins.Num() == 0);

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

FText UK2Node_LedgerTypedDomainTryGetValue::GetNodeTitle(ENodeTitleType::Type Title) const
{
	return FText::Format(NSLOCTEXT("LedgerNodes", "Nodes.LedgerTypedDomainTryGetValue.Title", "Try Get Value\nDomain: {0}"), FText::FromName(DomainName));
}

FText UK2Node_LedgerTypedDomainTryGetValue::GetTooltipText() const
{
	return NSLOCTEXT("LedgerNodes", "Nodes.LedgerTypedDomainTryGetValue.Tooltip", "Attempts to retrieve a value for the selected domain.");
}

TSharedPtr<SGraphNode> UK2Node_LedgerTypedDomainTryGetValue::CreateVisualWidget()
{
    return SNew(SGraphNode_LedgerTypedDomainTryGetValue, this);

}

void UK2Node_LedgerTypedDomainTryGetValue::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	// Locate the subsystem call
	const FName FunctionName = GET_FUNCTION_NAME_CHECKED(ULedgerSubsystem, TryGetValue);
	
	UK2Node_CallFunction* CallNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallNode->SetFromFunction(ULedgerSubsystem::StaticClass()->FindFunctionByName(FunctionName));
	CallNode->AllocateDefaultPins();
	
	// Move pins
	CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Domain Name")), *CallNode->FindPin(TEXT("Domain Name")));
	CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Value Name")), *CallNode->FindPin(TEXT("Value Name")));
	
	// Temp var for return value (bool)
	UEdGraphPin* BoolReturnPin = CallNode->GetReturnValuePin();
	
	// Create branching
	UK2Node_IfThenElse* BranchNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
	BranchNode->AllocateDefaultPins();
	
	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *BranchNode->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*BoolReturnPin, *BranchNode->GetConditionPin());
	
	// Route success/failure
	CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Success")), *BranchNode->GetThenPin());
	CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Failed")), *BranchNode->GetElsePin());
	
	// Move value output
	CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("Value")), *CallNode->FindPin(TEXT("OutValue")));
	
	// Done
	BreakAllNodeLinks();
	
	// // const FName FunctionName = GET_FUNCTION_NAME_CHECKED(UExampleFunctionsLibrary, SimpleEnumFunctionForNodeCustomized);
	// // UFunction* SimpleEnumFunctionForNodeCustomizedFunction = UExampleFunctionsLibrary::StaticClass()->FindFunctionByName(FunctionName);
	//
	// if (!SimpleEnumFunctionForNodeCustomizedFunction) {
	// 	CompilerContext.MessageLog.Error(*NSLOCTEXT("CustomizedBPNodes", "InvalidFunctionName", "The function has not been found.").ToString(), this);
	// 	return;
	// }
	//
	// UK2Node_CallFunction* SimpleEnumFunctionForNodeCustomized = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	// SimpleEnumFunctionForNodeCustomized->SetFromFunction(SimpleEnumFunctionForNodeCustomizedFunction);
	// SimpleEnumFunctionForNodeCustomized->AllocateDefaultPins();
	// CompilerContext.MessageLog.NotifyIntermediateObjectCreation(SimpleEnumFunctionForNodeCustomized, this);
	//
	//
	// // // The value is always the string version of the enum value
	// // SimpleEnumFunctionForNodeCustomized->FindPin(TEXT("ExampleEnum"))->DefaultValue = *ExampleEnumUtils::EnumToString(TEXT("EExampleEnum"), static_cast<int32>(EnumExample));
	//
	// //Exec pins
	// UEdGraphPin* NodeExec = GetExecPin();
	// UEdGraphPin* NodeThen = FindPin(UEdGraphSchema_K2::PN_Then);
	// UEdGraphPin* SimpleEnumFunctionForNodeCustomizedExecPin = SimpleEnumFunctionForNodeCustomized->GetExecPin();
	// UEdGraphPin* SimpleEnumFunctionForNodeCustomizedNodePin = SimpleEnumFunctionForNodeCustomized->GetThenPin();
	//
	// // Move Exec and Then links to internal node
	// CompilerContext.MovePinLinksToIntermediate(*NodeExec, *SimpleEnumFunctionForNodeCustomizedExecPin);
	// CompilerContext.MovePinLinksToIntermediate(*NodeThen, *SimpleEnumFunctionForNodeCustomizedNodePin);
	//
	// //After we are done we break all links to this node (not the internally created one)
	// BreakAllNodeLinks();
}