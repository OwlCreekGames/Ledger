// Copyright Owl Creek Games. All Rights Reserved.

/*
#include "LedgerSchemaEntryCustomization.h"

#include "LedgerSchemaConfig.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"

#define LOCTEXT_NAMESPACE "LedgerDomainSchemaEntryCustomization"

TSharedRef<IPropertyTypeCustomization> FLedgerSchemaEntryCustomization::MakeInstance()
{
	return MakeShareable(new FLedgerSchemaEntryCustomization);
}

void FLedgerSchemaEntryCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()];
}

void FLedgerSchemaEntryCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructHandle = StructPropertyHandle;
	CachedChildrenBuilder = &StructBuilder;
	PropertyUtilities = StructCustomizationUtils.GetPropertyUtilities();

	TypeProperty = StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, Type));
	check(TypeProperty.IsValid());

	// Watch for changes
	TypeProperty->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FLedgerSchemaEntryCustomization::OnTypeChanged));

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

	// Always show these
	StructBuilder.AddProperty(StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, Name)).ToSharedRef());
	StructBuilder.AddProperty(TypeProperty.ToSharedRef());

	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, DefaultInt32), ELedgerValueType::Int32);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, DefaultFloat), ELedgerValueType::Float);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, DefaultBool), ELedgerValueType::Bool);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, DefaultString), ELedgerValueType::String);

	StructBuilder.AddProperty(StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerSchemaRow, Description)).ToSharedRef());
}

void FLedgerSchemaEntryCustomization::OnTypeChanged()
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
*/
