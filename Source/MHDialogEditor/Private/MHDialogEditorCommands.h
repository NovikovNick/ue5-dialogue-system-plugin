// created by MetalHeart

#pragma once

#include "Framework/Commands/Commands.h"
#include "MHDialogEditorStyle.h"

namespace MH::Dialog::Private
{
class FMHDialogEditorCommands : public TCommands<FMHDialogEditorCommands>
{
  public:
	FMHDialogEditorCommands()
		: TCommands<FMHDialogEditorCommands>(TEXT("MHDialogEditor"),
											 NSLOCTEXT("Contexts", "MHDialogEditor", "MHDialogEditor Plugin"),
											 NAME_None,
											 FMHDialogEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

  public:
	TSharedPtr<FUICommandInfo> OpenPluginWindow;
};
}  // namespace MH::Dialog::Private
