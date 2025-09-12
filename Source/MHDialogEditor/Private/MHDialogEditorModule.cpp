// created by MetalHeart

#include "MHDialogEditorModule.h"

#include "Customization/MHDialogNodeDataCustomization.h"
#include "Graph/MHDialogGraphFactory.h"
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

	GraphPinFactory = MakeShared<FMHDialogGraphPinFactory>();
	FEdGraphUtilities::RegisterVisualPinFactory(GraphPinFactory);

	GraphNodeFactory = MakeShared<FMHDialogGraphNodeFactory>();
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphNodeFactory);
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

	FEdGraphUtilities::UnregisterVisualPinFactory(GraphPinFactory);
	FEdGraphUtilities::UnregisterVisualNodeFactory(GraphNodeFactory);
}

IMPLEMENT_MODULE(FMHDialogEditorModule, MHDialogEditor)
}  // namespace MH::Dialog::Private
#undef LOCTEXT_NAMESPACE
