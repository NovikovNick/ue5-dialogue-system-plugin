// created by MetalHeart

#include "MHDialogEditorStyle.h"

#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

#define RootToContentDir Style->RootToContentDir

namespace MH::Dialog::Private
{

TSharedPtr<FSlateStyleSet> FMHDialogEditorStyle::StyleInstance = nullptr;

void FMHDialogEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FMHDialogEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FMHDialogEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MHDialogEditorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);

TSharedRef<FSlateStyleSet> FMHDialogEditorStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShared<FSlateStyleSet>("MHDialogEditorStyle");

	// reuse app style
	Style->SetContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	Style->Set("MHDialogEditor.Undo", new IMAGE_BRUSH("Icons/icon_undo_16px", Icon16x16));
	Style->Set("MHDialogEditor.Redo", new IMAGE_BRUSH("Icons/icon_redo_16px", Icon16x16));

	// plugin's own resources
	// Style->SetContentRoot(IPluginManager::Get().FindPlugin("MHDialogEditor")->GetBaseDir() / TEXT("Resources"));

	return Style;
}

void FMHDialogEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FMHDialogEditorStyle::Get()
{
	return *StyleInstance;
}
}  // namespace MH::Dialog::Private
