// created by MetalHeart

#pragma once

#include "Styling/SlateStyle.h"

namespace MH::Dialog::Private
{
class FMHDialogEditorStyle
{
  public:
	static void Initialize();

	static void Shutdown();

	static void ReloadTextures();

	static const ISlateStyle& Get();

	static FName GetStyleSetName();

  private:
	static TSharedRef<class FSlateStyleSet> Create();

  private:
	static TSharedPtr<class FSlateStyleSet> StyleInstance;
};
}  // namespace MH::Dialog::Private
