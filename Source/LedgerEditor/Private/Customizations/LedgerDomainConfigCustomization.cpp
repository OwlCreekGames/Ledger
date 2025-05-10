// Copyright Owl Creek Games. All Rights Reserved.

#include "Customizations/LedgerDomainConfigCustomization.h"

#include "LedgerDomainConfig.h"
#include "LedgerTypedDomain.h" 
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IPropertyUtilities.h"
#include "PropertyHandle.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "FLedgerDomainDataCustomization"

TSharedRef<IDetailCustomization> FLedgerDomainConfigCustomization::MakeInstance()
{
	return MakeShareable(new FLedgerDomainConfigCustomization);
}

void FLedgerDomainConfigCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Domain");

	const TSharedPtr<IPropertyHandle> DomainNameHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(ULedgerDomainConfig, DomainName));
	if (DomainNameHandle.IsValid())
	{
		Category.AddProperty(DomainNameHandle.ToSharedRef());
	}
	
	const TSharedPtr<IPropertyHandle> DomainClassHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(ULedgerDomainConfig, DomainClass));
	if (DomainClassHandle.IsValid())
	{
		Category.AddProperty(DomainClassHandle.ToSharedRef());

		TSharedPtr<IPropertyUtilities> PropUtils = DetailBuilder.GetPropertyUtilities();
		DomainClassHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([PropUtils]()
		{
			if (PropUtils.IsValid())
			{
				PropUtils->ForceRefresh();
			}
		}));
	}
	
	const TSharedPtr<IPropertyHandle> SchemaAssetHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(ULedgerDomainConfig, SchemaAsset));
	if (DomainClassHandle.IsValid() && SchemaAssetHandle.IsValid())
	{
		UObject* DomainClassObj = nullptr;
		DomainClassHandle->GetValue(DomainClassObj);

		if (const UClass* SelectedClass = Cast<UClass>(DomainClassObj))
		{
			if (SelectedClass->IsChildOf(ULedgerTypedDomain::StaticClass()))
			{
				Category.AddProperty(SchemaAssetHandle.ToSharedRef());
			} else
			{
				DetailBuilder.HideProperty(SchemaAssetHandle);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
