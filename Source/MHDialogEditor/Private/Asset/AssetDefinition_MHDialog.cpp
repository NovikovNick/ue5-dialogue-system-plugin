// created by MetalHeart

#include "Asset/AssetDefinition_MHDialog.h"

#include "MHDialog.h"
#include "MHDialogEditorColors.h"
#include "MHDialogEditorLog.h"
#include "Toolkit/MHDialogToolkit.h"

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
	for (UMHDialog* Asset : OpenArgs.LoadObjects<UMHDialog>())
	{
		const double T0 = FPlatformTime::Seconds();
		MakeShared<MH::Dialog::Private::FMHDialogToolkit>()->InitDialogEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, Asset);
		const double T1 = FPlatformTime::Seconds();

		UE_LOG(LogMHDialogEditor, Display, TEXT("Dialog asset editor tooks %.1f seconds to open"), T1 - T0);

		Result = EAssetCommandResult::Handled;
	}
	return Result;
}
#undef LOCTEXT_NAMESPACE
