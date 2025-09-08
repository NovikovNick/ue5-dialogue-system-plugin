// created by MetalHeart

#include "MHDialogModule.h"

#define LOCTEXT_NAMESPACE "FMHDialogModule"

namespace MH::Dialog
{
void FMHDialogModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMHDialogModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
IMPLEMENT_MODULE(FMHDialogModule, MHDialog)
}  // namespace MH::Dialog
#undef LOCTEXT_NAMESPACE
