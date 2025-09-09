// created by MetalHeart

#pragma once

#include "Framework/Commands/Commands.h"

namespace MH::Dialog::Private
{
class FMHDialogEditorCommands final : public TCommands<FMHDialogEditorCommands>
{
  public:
	FMHDialogEditorCommands();

	//~ Begin TCommands<> interface
	virtual void RegisterCommands() override;
	//~ End TCommands<> interface

  public:
	TSharedPtr<FUICommandInfo> Undo;
	TSharedPtr<FUICommandInfo> Redo;
};
}  // namespace MH::Dialog::Private
