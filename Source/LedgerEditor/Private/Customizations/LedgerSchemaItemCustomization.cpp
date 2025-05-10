// Copyright Owl Creek Games. All Rights Reserved.

#include "Customizations/LedgerSchemaItemCustomization.h"

#include "DetailLayoutBuilder.h"
#include "LedgerSchemaConfig.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"

#define LOCTEXT_NAMESPACE "LedgerDomainSchemaEntryCustomization"

TSharedRef<IPropertyTypeCustomization> FLedgerSchemaItemCustomization::MakeInstance()
{
	return MakeShareable(new FLedgerSchemaItemCustomization);
}

void FLedgerSchemaItemCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	TSharedPtr<IPropertyUtilities> PropUtils = StructCustomizationUtils.GetPropertyUtilities();
	const TSharedPtr<IPropertyHandle> NameHandle = StructPropertyHandle->GetChildHandle("Name");

	FText DisplayName = LOCTEXT("DefaultItemLabel", "Item");
	if (NameHandle.IsValid())
	{
		FName RawName;
		if (NameHandle->GetValue(RawName) == FPropertyAccess::Success)
		{
			DisplayName = FText::FromName(RawName);
		}
	}

	if (NameHandle.IsValid() && PropUtils.IsValid())
	{
		NameHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([PropUtils]()
		{
			if (PropUtils.IsValid())
			{
				PropUtils->ForceRefresh();
			}
		}));
	}

	HeaderRow
	.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SBox)
		.MinDesiredWidth(300.f)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(DisplayName)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
	
	// .ValueContent()
	// .MinDesiredWidth(125.f)
	// .MaxDesiredWidth(600.f)
	// [
	// 	StructPropertyHandle->CreatePropertyValueWidget()
	// ];
}

void FLedgerSchemaItemCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructHandle = StructPropertyHandle;
	CachedChildrenBuilder = &StructBuilder;
	PropertyUtilities = StructCustomizationUtils.GetPropertyUtilities();

	TypeProperty = StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, Type));
	check(TypeProperty.IsValid());
	
	TypeProperty->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FLedgerSchemaItemCustomization::OnTypeChanged));

	uint8 TypeValue;
	TypeProperty->GetValue(TypeValue);

	const auto AddPropertyIf = [&](const FName& Name, const ELedgerValueType RequiredType) {
		if (static_cast<ELedgerValueType>(TypeValue) == RequiredType)
		{
			const TSharedPtr<IPropertyHandle> Prop = StructHandle->GetChildHandle(Name);
			if (Prop.IsValid())
			{
				StructBuilder.AddProperty(Prop.ToSharedRef());
			}
		}
	};
	
	StructBuilder.AddProperty(StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, Name)).ToSharedRef());
	StructBuilder.AddProperty(TypeProperty.ToSharedRef());

	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, DefaultInt32), ELedgerValueType::Int32);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, DefaultFloat), ELedgerValueType::Float);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, DefaultBool), ELedgerValueType::Bool);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, DefaultString), ELedgerValueType::String);

	StructBuilder.AddProperty(StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerSchemaItem, Description)).ToSharedRef());
}

void FLedgerSchemaItemCustomization::OnTypeChanged()
{
	if (StructHandle.IsValid() && StructHandle->IsValidHandle())
	{
		StructHandle->NotifyPostChange(EPropertyChangeType::ValueSet);

		if (PropertyUtilities.IsValid())
		{
			PropertyUtilities->ForceRefresh();
		}
	}
}

#undef LOCTEXT_NAMESPACE 
