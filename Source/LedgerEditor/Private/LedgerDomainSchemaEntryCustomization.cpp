// Copyright Owl Creek Games. All Rights Reserved.

#include "LedgerDomainSchemaEntryCustomization.h"

#include "LedgerDomainSchemaData.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"

#define LOCTEXT_NAMESPACE "LedgerDomainSchemaEntryCustomization"

TSharedRef<IPropertyTypeCustomization> FLedgerDomainSchemaEntryCustomization::MakeInstance()
{
	return MakeShareable(new FLedgerDomainSchemaEntryCustomization);
}

void FLedgerDomainSchemaEntryCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()];
}

void FLedgerDomainSchemaEntryCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructHandle = StructPropertyHandle;
	CachedChildrenBuilder = &StructBuilder;

	TypeProperty = StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, Type));
	check(TypeProperty.IsValid());

	// Watch for changes
	TypeProperty->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FLedgerDomainSchemaEntryCustomization::OnTypeChanged));

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
	StructBuilder.AddProperty(StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, Name)).ToSharedRef());
	StructBuilder.AddProperty(TypeProperty.ToSharedRef());

	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, DefaultInt32), ELedgerValueType::Int32);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, DefaultFloat), ELedgerValueType::Float);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, DefaultBool), ELedgerValueType::Bool);
	AddPropertyIf(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, DefaultString), ELedgerValueType::String);

	StructBuilder.AddProperty(StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLedgerDomainSchemaEntry, Description)).ToSharedRef());
}

void FLedgerDomainSchemaEntryCustomization::OnTypeChanged()
{
	if (StructHandle.IsValid() && StructHandle->IsValidHandle())
	{
		StructHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	}
}

#undef LOCTEXT_NAMESPACE
