// created by MetalHeart

#include "MHDialogEditorModule.h"

#include "Customization/MHDialogNodeDataCustomization.h"
#include "MHDialog.h"
#include "MHDialogEditorCommands.h"
#include "MHDialogEditorLog.h"
#include "MHDialogEditorStyle.h"
#include "MHDialogNodeData.h"

DEFINE_LOG_CATEGORY(LogMHDialogEditor)

#define LOCTEXT_NAMESPACE "FMHDialogEditorModule"

namespace MH::Dialog::Private
{
void FMHDialogEditorModule::StartupModule()
{
	FMHDialogEditorStyle::Get();
	FMHDialogEditorStyle::ReloadTextures();

	FMHDialogEditorCommands::Register();

	{  // clang-format off
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomPropertyTypeLayout(FMHDialogNodeData::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMHDialogNodeDataCustomization::MakeInstance));
		PropertyModule.NotifyCustomizationModuleChanged();
	}  // clang-format on
}

void FMHDialogEditorModule::ShutdownModule()
{
	FMHDialogEditorCommands::Unregister();

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(FMHDialogNodeData::StaticStruct()->GetFName());
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

IMPLEMENT_MODULE(FMHDialogEditorModule, MHDialogEditor)
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
