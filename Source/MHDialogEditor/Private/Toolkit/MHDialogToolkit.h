// created by MetalHeart

#pragma once

#include "AIGraphEditor.h"
#include "Tools/BaseAssetToolkit.h"

class UMHDialog;
class IDetailsView;
class IToolkitHost;
class SGraphEditor;
class UMHDialogGraph;

namespace MH::Dialog::Private
{

/*
 * The toolkit is supposed to act only as the UI manager
 */
class FMHDialogToolkit final : public FAssetEditorToolkit, public FAIGraphEditor
{
  public:
	void InitDialogEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMHDialog* Dialog);

	//~ Begin FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void OnClose() override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	//~ End FAssetEditorToolkit interface

  private:
	static const FName AppIdentifier;
	static const FName DetailsTabId;
	static const FName GraphTabId;

	TObjectPtr<UMHDialog> DialogAsset;
	TObjectPtr<UMHDialogGraph> DialogGraph;

	TSharedPtr<IDetailsView> DialogAssetDetailsView;
	TSharedPtr<IDetailsView> DialogNodeDetailsView;

	FDelegateHandle OnGraphUpdatedHandle;

	void CreateWidgets();
	void RegisterToolbar();
	void RegisterCommands();
	TSharedRef<FTabManager::FLayout> CreateLayout();
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Graph(const FSpawnTabArgs& Args);
	TSharedRef<IDetailsView> CreateDetailsView();

	void Undo();
	void Redo();
	void OnSelectedNodesChanged(const FGraphPanelSelectionSet& NewSelection);
	void OnFinishedChangingDetails(const FPropertyChangedEvent& Event);
	void OnGraphUpdated(const FEdGraphEditAction& Action);
	void OnNodeTextCommited(const FText&, ETextCommit::Type, UEdGraphNode*);
};

}  // namespace MH::Dialog::Private
