// created by MetalHeart

#pragma once

#include "Modules/ModuleManager.h"

namespace MH::Dialog::Private
{
class FMHDialogEditorModule : public IModuleInterface
{
  public:
	//~ Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface interface
  private:
	TSharedPtr<class FUICommandList> PluginCommands;

	void PluginButtonClicked();
	void RegisterMenus();
};

}  // namespace MH::Dialog::Private
