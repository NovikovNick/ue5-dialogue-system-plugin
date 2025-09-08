// created by MetalHeart

#include "MHDialogEditorModule.h"

#include "MHDialog.h"
#include "MHDialogEditorCommands.h"
#include "MHDialogEditorLog.h"
#include "MHDialogEditorStyle.h"
#include "ToolMenus.h"

DEFINE_LOG_CATEGORY(LogMHDialogEditor)

#define LOCTEXT_NAMESPACE "FMHDialogEditorModule"

namespace MH::Dialog::Private
{
void FMHDialogEditorModule::StartupModule()
{
	FMHDialogEditorStyle::Initialize();
	FMHDialogEditorStyle::ReloadTextures();

	FMHDialogEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(FMHDialogEditorCommands::Get().OpenPluginWindow,
							  FExecuteAction::CreateRaw(this, &FMHDialogEditorModule::PluginButtonClicked),
							  FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMHDialogEditorModule::RegisterMenus));
}

void FMHDialogEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FMHDialogEditorStyle::Shutdown();
	FMHDialogEditorCommands::Unregister();
}

void FMHDialogEditorModule::PluginButtonClicked()
{
	UMHDialog* Dialog = NewObject<UMHDialog>();
	UE_LOG(LogMHDialogEditor, Display, TEXT("Dialog.Topic is a %s"), *Dialog->Topic.ToString());
}

void FMHDialogEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry =
					Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMHDialogEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}
IMPLEMENT_MODULE(FMHDialogEditorModule, MHDialogEditor)
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
