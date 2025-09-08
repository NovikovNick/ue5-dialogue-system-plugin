// created by MetalHeart

#include "MHDialogEditorCommands.h"

#define LOCTEXT_NAMESPACE "FMHDialogEditorModule"

namespace MH::Dialog::Private
{
void FMHDialogEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MHDialogEditor", "Bring up MHDialogEditor window", EUserInterfaceActionType::Button, FInputChord());
}
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
