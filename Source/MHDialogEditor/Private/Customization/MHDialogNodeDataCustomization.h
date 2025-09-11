// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

namespace MH::Dialog::Private
{

class FMHDialogNodeDataCustomization : public IPropertyTypeCustomization
{
  public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//~ Begin IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
								 FDetailWidgetRow& HeaderRow,
								 IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
								   IDetailChildrenBuilder& ChildBuilder,
								   IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	//~ End IPropertyTypeCustomization interface

  private:
	TSharedRef<SWidget> OnGetComboContent();

	FText GetTitle() const;
	void SetTitle(int32 Index);

	TSharedPtr<IPropertyHandle> TitleProperty;

	TArray<FText> NodeContentValues;
};

}  // namespace MH::Dialog::Private