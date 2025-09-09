// created by MetalHeart

#include "Toolkit/MHDialogToolkit.h"

#include "MHDialog.h"
#include "MHDialogEditorColors.h"
#include "MHDialogEditorCommands.h"
#include "MHDialogEditorLog.h"
#include "MHDialogEditorStyle.h"
#include "MHDialogEditorSubsystem.h"

#define LOCTEXT_NAMESPACE "MHDialogToolkit"

namespace MH::Dialog::Private
{
const FName FMHDialogToolkit::AppIdentifier(TEXT("MHDialogAssetEditor"));
const FName FMHDialogToolkit::DetailsTabId(TEXT("FMHDialogToolkit_Details"));
const FName FMHDialogToolkit::GraphTabId(TEXT("FMHDialogToolkit_Graph"));

FText FMHDialogToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "MHDialog Asset");
}

FName FMHDialogToolkit::GetToolkitFName() const
{
	return AppIdentifier;
}

FString FMHDialogToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "MHDialog Asset ").ToString();
}

FLinearColor FMHDialogToolkit::GetWorldCentricTabColorScale() const
{
	return Colors::Asset::WorldCentricTabColorScale;
}

void FMHDialogToolkit::InitDialogEditor(const EToolkitMode::Type Mode,
										const TSharedPtr<class IToolkitHost>& InitToolkitHost,
										UMHDialog* Dialog)
{
	DialogAsset = Dialog;
	check(IsValid(DialogAsset));

	GEditor->GetEditorSubsystem<UMHDialogEditorSubsystem>()->InitAsset(DialogAsset);

	CreateWidgets();
	RegisterToolbar();
	RegisterCommands();
	TSharedRef<FTabManager::FLayout> Layout = CreateLayout();

	FAssetEditorToolkit::InitAssetEditor(Mode,
										 InitToolkitHost,
										 GetToolkitFName(),
										 Layout,
										 /* bCreateDefaultStandaloneMenu */ true,
										 /* bCreateDefaultToolbar */ true,
										 DialogAsset);
}

void FMHDialogToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	check(AssetEditorTabsCategory.IsValid());

	InTabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &FMHDialogToolkit::SpawnTab_Details))
		.SetDisplayName(LOCTEXT("Details", "Details"))
		.SetGroup(AssetEditorTabsCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(GraphTabId, FOnSpawnTab::CreateSP(this, &FMHDialogToolkit::SpawnTab_Graph))
		.SetDisplayName(LOCTEXT("Graph", "Graph"))
		.SetGroup(AssetEditorTabsCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FMHDialogEditorStyle::StyleSetName(), FMHDialogEditorStyle::GraphTab));
}

void FMHDialogToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(DetailsTabId);
	InTabManager->UnregisterTabSpawner(GraphTabId);
}

void FMHDialogToolkit::CreateWidgets()
{
	DialogAssetDetailsView = CreateDetailsView();
	DialogAssetDetailsView->SetObject(DialogAsset);
}

void FMHDialogToolkit::RegisterToolbar()
{
	FToolMenuOwnerScoped ToolMenuOwnerScope(this);

	FName ParentName;
	const FName MenuName   = GetToolMenuToolbarName(ParentName);
	UToolMenus* ToolMenus  = UToolMenus::Get();
	UToolMenu* ToolbarMenu = ToolMenus->ExtendMenu(MenuName);
	if (!ToolMenus->IsMenuRegistered(MenuName))
	{
		ToolbarMenu = ToolMenus->RegisterMenu(MenuName, ParentName, EMultiBoxType::ToolBar);
	}

	FToolMenuInsert InsertAfterAssetSection("Asset", EToolMenuInsertType::After);
	{
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Generic", {}, InsertAfterAssetSection);
		Section.AddMenuEntry(FMHDialogEditorCommands::Get().Undo, FText::GetEmpty());
		Section.AddMenuEntry(FMHDialogEditorCommands::Get().Redo, FText::GetEmpty());
	}
}

void FMHDialogToolkit::RegisterCommands()
{
	GetToolkitCommands()->MapAction(FMHDialogEditorCommands::Get().Undo, FExecuteAction::CreateSP(this, &FMHDialogToolkit::Undo));
	GetToolkitCommands()->MapAction(FMHDialogEditorCommands::Get().Redo, FExecuteAction::CreateSP(this, &FMHDialogToolkit::Redo));
}

TSharedRef<FTabManager::FLayout> FMHDialogToolkit::CreateLayout()
{
	// clang-format off
	return FTabManager::NewLayout(TEXT("Standalone_FMHDialogToolkit_v2"))
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->AddTab(GraphTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.3f)
					->AddTab(DetailsTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
			)
		);
	// clang-format on
}

TSharedRef<SDockTab> FMHDialogToolkit::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	// clang-format off
	return SNew(SDockTab)
		.Label(LOCTEXT("BaseDetailsTitle", "Details"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.Padding(0, 8, 0, 0)
			.AutoHeight()
			[
				DialogAssetDetailsView.ToSharedRef()
			]
		];
	// clang-format on
}

TSharedRef<SDockTab> FMHDialogToolkit::SpawnTab_Graph(const FSpawnTabArgs& Args)
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("GraphCornerText", "DIALOGUE SYSTEM");

	// clang-format off
	return SNew(SDockTab)
		.Label(LOCTEXT("GraphLabel", "Dialogue Graph"))
		[
			SNew(SGraphEditor)
			.Appearance(AppearanceInfo)
			.GraphToEdit(DialogAsset->Graph)
		];
	// clang-format on
}

TSharedRef<IDetailsView> FMHDialogToolkit::CreateDetailsView()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings  = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;
	return PropertyEditorModule.CreateDetailView(DetailsViewArgs);
}

void FMHDialogToolkit::Undo()
{
	if (UEditorEngine* Editor = Cast<UEditorEngine>(GEngine))
	{
		Editor->UndoTransaction(/*bCanRedo*/ true);
	}
}

void FMHDialogToolkit::Redo()
{
	if (UEditorEngine* Editor = Cast<UEditorEngine>(GEngine))
	{
		Editor->RedoTransaction();
	}
}
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
