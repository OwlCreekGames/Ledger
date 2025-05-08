// Copyright Owl Creek Games. All Rights Reserved.

#include "GraphPin_LedgerDomainName.h"
#include "Widgets/Input/SComboBox.h"
#include "LedgerSubsystem.h"
#include "Editor.h"

void SGraphPin_LedgerDomainName::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
    SetPinObj(InPin);
    
    LoadDomainNames();
    SGraphPin::Construct(SGraphPin::FArguments(), InPin);
}

void SGraphPin_LedgerDomainName::LoadDomainNames()
{
    DomainNames.Reset();

    if (GEditor)
    {
        if (UWorld* World = GEditor->GetEditorWorldContext().World())
        {
            if (ULedgerSubsystem* Subsystem = World->GetSubsystem<ULedgerSubsystem>())
            {
                TArray<FName> Names = Subsystem->GetTypedDomainNames();
                for (const FName& Name : Names)
                {
                    DomainNames.Add(MakeShared<FName>(Name));
                }
            }
        }
    }
    
    if (GetPinObj()->DefaultValue != TEXT(""))
    {
        SelectedName = MakeShared<FName>(FName(*GetPinObj()->DefaultValue));
    }
}

TSharedRef<SWidget> SGraphPin_LedgerDomainName::GetDefaultValueWidget()
{
    return SNew(SComboBox<TSharedPtr<FName>>)
        .OptionsSource(&DomainNames)
        .OnSelectionChanged(this, &SGraphPin_LedgerDomainName::OnSelectionChanged)
        .OnGenerateWidget(this, &SGraphPin_LedgerDomainName::OnGenerateWidget)
        .InitiallySelectedItem(SelectedName)
        [
            SNew(STextBlock).Text(this, &SGraphPin_LedgerDomainName::GetSelectedText)
        ];
}

void SGraphPin_LedgerDomainName::OnSelectionChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type)
{
    if (NewSelection.IsValid())
    {
        SelectedName = NewSelection;
        GetPinObj()->GetSchema()->TrySetDefaultValue(*GetPinObj(), SelectedName->ToString());
    }
}

TSharedRef<SWidget> SGraphPin_LedgerDomainName::OnGenerateWidget(TSharedPtr<FName> InItem) const
{
    return SNew(STextBlock).Text(FText::FromName(*InItem));
}

FText SGraphPin_LedgerDomainName::GetSelectedText() const
{
    return SelectedName.IsValid() ? FText::FromName(*SelectedName) : FText::FromString(TEXT("None"));
}

