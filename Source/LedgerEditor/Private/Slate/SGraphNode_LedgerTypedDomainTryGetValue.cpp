// Copyright Owl Creek Games. All Rights Reserved.


#include "SGraphNode_LedgerTypedDomainTryGetValue.h"

#include "LedgerSubsystem.h"
#include "SlateOptMacros.h"
#include "SNameComboBox.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Nodes/K2Node_LedgerTypedDomainTryGetValue.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGraphNode_LedgerTypedDomainTryGetValue::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;
    
	UpdateGraphNode();
}

void SGraphNode_LedgerTypedDomainTryGetValue::CreatePinWidgets()
{
	SGraphNodeK2Base::CreatePinWidgets();

	// Look into supporting the value in the node like this example did ....
	auto* CustomizedNode = Cast<UK2Node_LedgerTypedDomainTryGetValue>(GraphNode);

	LeftNodeBox->AddSlot()
	.AutoHeight()
	.Padding(FMargin { 32, 4, 4, 4})
	[
		SNew(STextBlock)
			.Text(NSLOCTEXT("CustomizedBPNodes", "Label.ExampleString", "Example String Value"))
			.TextStyle(FAppStyle::Get(), "Graph.Node.PinName")
			.IsEnabled(this, &SGraphNodeK2Base::IsNodeEditable)
	];

	LeftNodeBox->AddSlot()
	.AutoHeight()
	.Padding(FMargin { 36, 4, 4, 4 })
	[
		// SNew(SEditableText)
		// .Text(FText::FromString(CustomizedNode->ExampleString))
		// .HintText(NSLOCTEXT("CustomizedBPNodes", "Label.DialogPlaceholderText", "Enter example string..."))
		// .OnTextChanged(this, &SGraphNode_LedgerTypedDomainTryGetValue::OnExampleStringChanged)
		// .IsEnabled(this, &SGraphNodeK2Base::IsNodeEditable)


		MakeDomainSelector()
	];

}


TSharedRef<SWidget> SGraphNode_LedgerTypedDomainTryGetValue::MakeDomainSelector()
{
	// Load domain names from subsystem
	DomainNames.Reset();
	if (GEditor && GEditor->GetEditorWorldContext().World())
	{
		if (ULedgerSubsystem* Subsystem = GEditor->GetEditorWorldContext().World()->GetSubsystem<ULedgerSubsystem>())
		{	
			for (FName Name : Subsystem->GetTypedDomainNames())
			{
				DomainNames.Add(MakeShared<FName>(Name));
			}
		}
	}

	UK2Node_LedgerTypedDomainTryGetValue* TypedNode = Cast<UK2Node_LedgerTypedDomainTryGetValue>(GraphNode);
	if (TypedNode)
	{
		SelectedDomain = MakeShared<FName>(TypedNode->DomainName);
	}

	FSlateFontInfo LabelFont = FCoreStyle::GetDefaultFontStyle("Regular", 9);
    
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(8.f, 2.f, 8.f, 2.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Domain Name:"))
			.Font(LabelFont)
			.ColorAndOpacity(FLinearColor::White)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(8.f, 2.f, 8.f, 2.f)
		[
			SNew(SComboBox<TSharedPtr<FName>>)
			.OptionsSource(&DomainNames)
			.OnSelectionChanged(this, &SGraphNode_LedgerTypedDomainTryGetValue::OnDomainChanged)
			.OnGenerateWidget(this, &SGraphNode_LedgerTypedDomainTryGetValue::OnGenerateDomainItem)
			.InitiallySelectedItem(SelectedDomain)
			[
				SNew(STextBlock).Text(this, &SGraphNode_LedgerTypedDomainTryGetValue::GetSelectedDomainText)
			]
		];
}

// void SGraphNode_LedgerTypedDomainTryGetValue::OnExampleStringChanged(const FText& DialogText)
// {
// 	auto* SimpleFunctionCustomizedNode = Cast<UK2Node_LedgerTypedDomainTryGetValue>(GraphNode);
//
// 	SimpleFunctionCustomizedNode->Modify();
// 	SimpleFunctionCustomizedNode->ExampleString = DialogText.ToString();
// 	FBlueprintEditorUtils::MarkBlueprintAsModified(SimpleFunctionCustomizedNode->GetBlueprint());
// }

void SGraphNode_LedgerTypedDomainTryGetValue::OnDomainChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type)
{
	if (UK2Node_LedgerTypedDomainTryGetValue* TypedNode = Cast<UK2Node_LedgerTypedDomainTryGetValue>(GraphNode))
	{
		if (NewSelection.IsValid())
		{
			TypedNode->Modify();
			TypedNode->DomainName = *NewSelection;
			SelectedDomain = NewSelection;
		}
	}
}

TSharedRef<SWidget> SGraphNode_LedgerTypedDomainTryGetValue::OnGenerateDomainItem(TSharedPtr<FName> InItem) const
{
	return SNew(STextBlock).Text(FText::FromName(*InItem));
}

FText SGraphNode_LedgerTypedDomainTryGetValue::GetSelectedDomainText() const
{
	return SelectedDomain.IsValid() ? FText::FromName(*SelectedDomain) : FText::FromString("Select Domain");
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION
