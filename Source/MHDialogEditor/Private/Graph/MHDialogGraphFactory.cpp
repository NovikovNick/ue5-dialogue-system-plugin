#include "Graph/MHDialogGraphFactory.h"

#include "Graph/MHDialogGraphNode.h"
#include "Graph/MHDialogGraphSchema.h"
#include "Widget/SMHDialogGraphNode.h"
#include "Widget/SMHDialogGraphNodePin.h"

namespace MH::Dialog::Private
{

TSharedPtr<SGraphNode> FMHDialogGraphNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UMHDialogGraphNode* DialogNode = Cast<UMHDialogGraphNode>(Node))
	{
		return SNew(SMHDialogGraphNode, DialogNode);
	}

	return nullptr;
}

TSharedPtr<SGraphPin> FMHDialogGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	if (UMHDialogGraphSchema::PC_Default == InPin->PinType.PinSubCategory)
	{
		return SNew(SMHDialogGraphNodePin, InPin);
	}
	return nullptr;
}

}  // namespace MH::Dialog::Private