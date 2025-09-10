// created by MetalHeart

#pragma once

#include "Tools/BaseAssetToolkit.h"

class UMHDialog;
class IDetailsView;
class IToolkitHost;
class SGraphEditor;

namespace MH::Dialog::Private
{

/*
 * The toolkit is supposed to act only as the UI manager
 */
class FMHDialogToolkit final : public FAssetEditorToolkit, public FEditorUndoClient
{
  public:
	FMHDialogToolkit();
	virtual ~FMHDialogToolkit();

	void InitDialogEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMHDialog* Dialog);

	//~ Begin FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	//~ End FAssetEditorToolkit interface

	//~ Begin FEditorUndoClient Interface
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	// End of FEditorUndoClient

  private:
	static const FName AppIdentifier;
	static const FName DetailsTabId;
	static const FName GraphTabId;

	TObjectPtr<UMHDialog> DialogAsset;

	TSharedPtr<IDetailsView> DialogAssetDetailsView;
	TWeakPtr<SGraphEditor> UpdateGraphEdPtr;

	void CreateWidgets();
	void RegisterToolbar();
	void RegisterCommands();
	TSharedRef<FTabManager::FLayout> CreateLayout();
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Graph(const FSpawnTabArgs& Args);
	TSharedRef<IDetailsView> CreateDetailsView();

	void Undo();
	void Redo();
};

}  // namespace MH::Dialog::Private
