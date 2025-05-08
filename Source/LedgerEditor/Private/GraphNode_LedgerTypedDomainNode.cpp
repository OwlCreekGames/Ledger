// Copyright Owl Creek Games. All Rights Reserved.

#include "GraphNode_LedgerTypedDomainNode.h"

/*
void SGraphNode_LedgerTypedDomainNode::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
    GraphNode = InNode;
    SetCursor(EMouseCursor::CardinalCross);
    UpdateGraphNode();
}

void SGraphNode_LedgerTypedDomainNode::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
    MainBox->AddSlot()
    .AutoHeight()
    .Padding(5.f)
    [
        MakeDomainSelector()
    ];
}

TSharedRef<SWidget> SGraphNode_LedgerTypedDomainNode::MakeDomainSelector()
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

    ULedgerTypedDomainK2Node_TryGetValue* TypedNode = Cast<ULedgerTypedDomainK2Node_TryGetValue>(GraphNode);
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
            .OnSelectionChanged(this, &SGraphNode_LedgerTypedDomainNode::OnDomainChanged)
            .OnGenerateWidget(this, &SGraphNode_LedgerTypedDomainNode::OnGenerateDomainItem)
            .InitiallySelectedItem(SelectedDomain)
            [
                SNew(STextBlock).Text(this, &SGraphNode_LedgerTypedDomainNode::GetSelectedDomainText)
            ]
        ];
}

void SGraphNode_LedgerTypedDomainNode::OnDomainChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type)
{
    if (ULedgerTypedDomainK2Node_TryGetValue* TypedNode = Cast<ULedgerTypedDomainK2Node_TryGetValue>(GraphNode))
    {
        if (NewSelection.IsValid())
        {
            TypedNode->Modify();
            TypedNode->DomainName = *NewSelection;
            SelectedDomain = NewSelection;
        }
    }
}

TSharedRef<SWidget> SGraphNode_LedgerTypedDomainNode::OnGenerateDomainItem(TSharedPtr<FName> InItem) const
{
    return SNew(STextBlock).Text(FText::FromName(*InItem));
}

FText SGraphNode_LedgerTypedDomainNode::GetSelectedDomainText() const
{
    return SelectedDomain.IsValid() ? FText::FromName(*SelectedDomain) : FText::FromString("Select Domain");
}

*/