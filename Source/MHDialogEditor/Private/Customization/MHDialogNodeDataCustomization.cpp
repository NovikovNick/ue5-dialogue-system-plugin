// created by MetalHeart

#include "Customization/MHDialogNodeDataCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Graph/MHDialogGraphNode.h"
#include "IDetailChildrenBuilder.h"
#include "MHDialogEditorLog.h"
#include "MHDialogNode.h"

#define LOCTEXT_NAMESPACE "FMHDialogNodeDataCustomization"
namespace MH::Dialog::Private
{

TSharedRef<IPropertyTypeCustomization> FMHDialogNodeDataCustomization::MakeInstance()
{
	return MakeShared<FMHDialogNodeDataCustomization>();
}

void FMHDialogNodeDataCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
													 FDetailWidgetRow& HeaderRow,
													 IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	TitleProperty = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMHDialogNodeData, Content));

	NodeContentValues.Reset();
	NodeContentValues.Add(LOCTEXT("Hello", "Hello, player!"));
	NodeContentValues.Add(LOCTEXT("HRU", "How're you doing?"));

	// clang-format off
	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SComboButton)
		.OnGetMenuContent(this, &FMHDialogNodeDataCustomization::OnGetComboContent)
		.ContentPadding(FMargin(2.0f, 2.0f))
		.ButtonContent()
		[
			SNew(STextBlock)
			.Text(this, &FMHDialogNodeDataCustomization::GetTitle)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]

	];
	// clang-format on
}

void FMHDialogNodeDataCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropHandle,
													   IDetailChildrenBuilder& ChildBuilder,
													   IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	ChildBuilder.AddProperty(TitleProperty.ToSharedRef());

	TSharedPtr<IPropertyHandle> ReadDuration = PropHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMHDialogNodeData, ReadDurationSec));
	ChildBuilder.AddProperty(ReadDuration.ToSharedRef());
}

TSharedRef<SWidget> FMHDialogNodeDataCustomization::OnGetComboContent()
{
	FMenuBuilder MenuBuilder(true, nullptr);
	for (int32 i = 0; i < NodeContentValues.Num(); i++)
	{
		FUIAction ItemAction(FExecuteAction::CreateSP(this, &FMHDialogNodeDataCustomization::SetTitle, i));
		MenuBuilder.AddMenuEntry(NodeContentValues[i], TAttribute<FText>(), FSlateIcon(), MoveTemp(ItemAction));
	}
	return MenuBuilder.MakeWidget();
}

FText FMHDialogNodeDataCustomization::GetTitle() const
{
	if (TitleProperty.IsValid())
	{
		FText Val;
		if (TitleProperty->GetValue(Val) == FPropertyAccess::Result::Success)
		{
			return Val;
		}
	}
	return FText::GetEmpty();
}

void FMHDialogNodeDataCustomization::SetTitle(int32 Index)
{
	if (TitleProperty.IsValid())
	{
		if (TitleProperty->SetValue(NodeContentValues[Index].ToString()) == FPropertyAccess::Result::Success)
		{
			TitleProperty->NotifyFinishedChangingProperties();
		}
	}
}

}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE