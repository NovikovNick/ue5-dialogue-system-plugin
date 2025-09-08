// created by MetalHeart

#include "Asset/AssetDefinition_MHDialog.h"

#include "MHDialog.h"
#include "MHDialogEditorColors.h"
#include "MHDialogEditorLog.h"

#define LOCTEXT_NAMESPACE "UAssetDefinition_MHDialog"

FText UAssetDefinition_MHDialog::GetAssetDisplayName() const
{
	return LOCTEXT("UAssetDefinition_Dialog", "Dialogue Asset");
}

FLinearColor UAssetDefinition_MHDialog::GetAssetColor() const
{
	return MH::Dialog::Private::Colors::Asset::Default;
}

TSoftClassPtr<> UAssetDefinition_MHDialog::GetAssetClass() const
{
	return UMHDialog::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_MHDialog::GetAssetCategories() const
{
	static const FAssetCategoryPath Categories[] = {FAssetCategoryPath(LOCTEXT("Category", "Dialogue System"))};
	return Categories;
}

EAssetCommandResult UAssetDefinition_MHDialog::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	EAssetCommandResult Result = EAssetCommandResult::Unhandled;

	return Result;
}
#undef LOCTEXT_NAMESPACE
