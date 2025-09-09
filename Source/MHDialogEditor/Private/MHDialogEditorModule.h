// created by MetalHeart

#pragma once

#include "Modules/ModuleManager.h"

namespace MH::Dialog::Private
{
class FMHDialogEditorModule final : public IModuleInterface
{
  public:
	//~ Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface interface
};
}  // namespace MH::Dialog::Private
