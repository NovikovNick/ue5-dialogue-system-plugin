// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class SGraphNode;
class SGraphPin;

namespace MH::Dialog::Private
{

struct FMHDialogGraphNodeFactory : FGraphPanelNodeFactory
{
  public:
	virtual TSharedPtr<SGraphNode> CreateNode(class UEdGraphNode* Node) const override;
};

struct FMHDialogGraphPinFactory : public FGraphPanelPinFactory
{
  public:
	virtual TSharedPtr<SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;
};

}  // namespace MH::Dialog::Private
