// Copyright Owl Creek Games. All Rights Reserved.

#include "Customizations/LedgerSchemaConfigCustomization.h"

#include "LedgerDomainConfig.h"
#include "LedgerTypedDomain.h" 
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IPropertyUtilities.h"
#include "LedgerSchemaConfig.h"
#include "PropertyHandle.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "FLedgerDomainDataCustomization"

TSharedRef<IDetailCustomization> FLedgerSchemaConfigCustomization::MakeInstance()
{
	return MakeShareable(new FLedgerSchemaConfigCustomization);
}

void FLedgerSchemaConfigCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Schema");

	TSharedRef<IPropertyHandle> Entries = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(ULedgerSchemaConfig, Items));

	uint32 NumElements = 0;
	Entries->GetNumChildren(NumElements);
	
	for (uint32 Index = 0; Index < NumElements; ++Index)
	{
		TSharedPtr<IPropertyHandle> ElementHandle = Entries->GetChildHandle(Index);
		if (ElementHandle.IsValid())
		{
			TSharedPtr<IPropertyHandle> NameHandle = ElementHandle->GetChildHandle("Name");
			FText DisplayName = FText::Format(FText::FromString("Item [{0}]"), FText::AsNumber(Index)); // fallback

			if (NameHandle.IsValid() && NameHandle->IsValidHandle())
			{
				FName RawName;
				if (NameHandle->GetValue(RawName) == FPropertyAccess::Success)
				{
					DisplayName = FText::FromName(RawName);
				}
			
				Category.AddProperty(ElementHandle.ToSharedRef())
					.CustomWidget()
					.NameContent()
					[
						SNew(STextBlock)
						.Text(DisplayName)
						.Font(IDetailLayoutBuilder::GetDetailFont())
					]
					.ValueContent()
					[
						ElementHandle->CreatePropertyValueWidget()
					];
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE