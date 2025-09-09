// created by MetalHeart

#include "MHDialogEditorStyle.h"

#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

namespace MH::Dialog::Private
{

const FName FMHDialogEditorStyle::Undo(TEXT("MHDialogEditor.Undo"));
const FName FMHDialogEditorStyle::Redo(TEXT("MHDialogEditor.Redo"));
const FName FMHDialogEditorStyle::GraphTab(TEXT("MHDialogEditor.GraphTab"));

FMHDialogEditorStyle::FMHDialogEditorStyle() : FSlateStyleSet(TEXT("MHDialogEditorStyle"))
{
	const FVector2D Icon16x16(16.0f, 16.0f);

	// reuse app style
	SetContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	Set(Undo, new IMAGE_BRUSH("Icons/icon_undo_16px", Icon16x16));
	Set(Redo, new IMAGE_BRUSH("Icons/icon_redo_16px", Icon16x16));

	SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor") / TEXT("Slate"));
	Set(GraphTab, new IMAGE_BRUSH("Icons/icon_Blueprint_EventGraph_16x", Icon16x16));

	// plugin's own resources
	// Style->SetContentRoot(IPluginManager::Get().FindPlugin("MHDialogEditor")->GetBaseDir() / TEXT("Resources"));

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FMHDialogEditorStyle::~FMHDialogEditorStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

const FName& FMHDialogEditorStyle::StyleSetName()
{
	return FMHDialogEditorStyle::Get().GetStyleSetName();
}

const ISlateStyle& FMHDialogEditorStyle::Get()
{
	static FMHDialogEditorStyle Instance;
	return Instance;
}

void FMHDialogEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

}  // namespace MH::Dialog::Private