// created by MetalHeart

#pragma once

#include "Modules/ModuleManager.h"

namespace MH::Dialog::Private
{

struct FMHDialogGraphNodeFactory;
struct FMHDialogGraphPinFactory;

class FMHDialogEditorModule final : public IModuleInterface
{
  public:
	//~ Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface interface
  private:
	TSharedPtr<FMHDialogGraphPinFactory> GraphPinFactory;
	TSharedPtr<FMHDialogGraphNodeFactory> GraphNodeFactory;
};
}  // namespace MH::Dialog::Private
