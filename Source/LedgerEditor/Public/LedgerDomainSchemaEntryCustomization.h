// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "IPropertyTypeCustomization.h"

class FLedgerDomainSchemaEntryCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
		FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
		IDetailChildrenBuilder& StructBuilder,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	void OnTypeChanged();

	TSharedPtr<IPropertyHandle> TypeProperty;
	TSharedPtr<IPropertyHandle> StructHandle;
	IDetailChildrenBuilder* CachedChildrenBuilder = nullptr;
};
