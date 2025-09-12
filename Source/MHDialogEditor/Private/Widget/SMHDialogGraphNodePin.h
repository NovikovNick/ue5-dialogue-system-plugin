// created by MetalHeart

#pragma once

#include "MHDialogEditorColors.h"
#include "SGraphNodeAI.h"

namespace MH::Dialog::Private
{

class SMHDialogGraphNodePin : public SGraphPinAI
{
	SLATE_BEGIN_ARGS(SMHDialogGraphNodePin) {}
	SLATE_END_ARGS();

	//~ Begin SGraphPin interface
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPinAI::Construct(SGraphPinAI::FArguments(), InGraphPinObj);
	}

  protected:
	virtual FSlateColor GetPinColor() const override
	{
		return IsHovered() ? FSlateColor(Colors::Node::Pin::Hover) : FSlateColor(Colors::Node::Pin::Default);
	}
	//~ End SGraphPin interface
};

}  // namespace MH::Dialog::Private
