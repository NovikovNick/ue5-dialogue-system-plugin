// created by MetalHeart

#include "MHDialogEditorCommands.h"

#include "MHDialogEditorStyle.h"

#define LOCTEXT_NAMESPACE "FMHDialogEditorModule"

namespace MH::Dialog::Private
{
FMHDialogEditorCommands::FMHDialogEditorCommands()
	: TCommands<FMHDialogEditorCommands>(
		  TEXT("MHDialogEditor"),									// Context name for fast lookup
		  LOCTEXT("MHDialogEditor", "MetalHeart's Dialog Editor"),	// Localized context name for displaying
		  NAME_None,												// Parent
		  FMHDialogEditorStyle::GetStyleSetName()					// Icon Style Set
	  )
{
}
void FMHDialogEditorCommands::RegisterCommands()
{
	UI_COMMAND(Undo, "Undo", "Undo operation", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Redo, "Redo", "Redo operation", EUserInterfaceActionType::Button, FInputChord());
}
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
