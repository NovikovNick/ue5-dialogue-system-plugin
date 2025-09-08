// created by MetalHeart

#include "MHDialogEditorModule.h"

#include "MHDialog.h"
#include "MHDialogEditorCommands.h"
#include "MHDialogEditorLog.h"
#include "MHDialogEditorStyle.h"

DEFINE_LOG_CATEGORY(LogMHDialogEditor)

#define LOCTEXT_NAMESPACE "FMHDialogEditorModule"

namespace MH::Dialog::Private
{
void FMHDialogEditorModule::StartupModule()
{
	FMHDialogEditorStyle::Initialize();
	FMHDialogEditorStyle::ReloadTextures();

	FMHDialogEditorCommands::Register();
}

void FMHDialogEditorModule::ShutdownModule()
{
	FMHDialogEditorStyle::Shutdown();
	FMHDialogEditorCommands::Unregister();
}

IMPLEMENT_MODULE(FMHDialogEditorModule, MHDialogEditor)
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
