// created by MetalHeart

#pragma once

#include "Styling/SlateStyle.h"

namespace MH::Dialog::Private
{
class FMHDialogEditorStyle final : public FSlateStyleSet
{
  public:
	static const FName Undo;
	static const FName Redo;
	static const FName GraphTab;

	static const ISlateStyle& Get();
	static const FName& StyleSetName();
	static void ReloadTextures();

  private:
	FMHDialogEditorStyle();
	virtual ~FMHDialogEditorStyle() override;
};
}  // namespace MH::Dialog::Private
