// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "SGraphNodeAI.h"

class UMHDialogGraphNode;

namespace MH::Dialog::Private
{

class SMHDialogGraphNode : public SGraphNodeAI
{
  public:
	SLATE_BEGIN_ARGS(SMHDialogGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UMHDialogGraphNode* InNode);

	//~ Begin SGraphNode interface
	virtual void UpdateGraphNode() override;
	//~ End SGraphNode interface

  private:
	// FText GetTitle() const;
	FSlateColor GetBorderBackgroundColor() const;
	FSlateColor GetBackgroundColor() const;
};

}  // namespace MH::Dialog::Private
