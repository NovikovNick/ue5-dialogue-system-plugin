// created by MetalHeart

#include "Graph/MHDialogGraphNode.h"

#include "Graph/MHDialogGraphSchema.h"
#include "MHDialogEditorColors.h"

FText UMHDialogGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return bRootNode ? FText::FromString(TEXT("Root Node")) : FText::FromString(TEXT("Node"));
}

FLinearColor UMHDialogGraphNode::GetNodeTitleColor() const
{
	return MH::Dialog::Private::Colors::Node::Title::Default;
};

void UMHDialogGraphNode::AllocateDefaultPins()
{
	if (!bRootNode)
	{
		UEdGraphPin* InputPin			 = CreatePin(EEdGraphPinDirection::EGPD_Input, TEXT("Input"), NAME_None);
		InputPin->PinType.PinSubCategory = UMHDialogGraphSchema::PC_Default;
	}

	UEdGraphPin* InputPin			 = CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Output"), NAME_None);
	InputPin->PinType.PinSubCategory = UMHDialogGraphSchema::PC_Default;

	GetGraph()->NotifyGraphChanged();
	GetGraph()->Modify();
}

void UMHDialogGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		UEdGraphPin* OutputPin = GetOutputPin();

		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
		else if (OutputPin != nullptr && GetSchema()->TryCreateConnection(OutputPin, FromPin))
		{
			NodeConnectionListChanged();
		}
	}
}

UEdGraphPin* UMHDialogGraphNode::GetInputPin(int32 InputIndex) const
{
	check(InputIndex >= 0);

	for (int32 PinIndex = 0, FoundInputs = 0; PinIndex < Pins.Num(); PinIndex++)
	{
		if (Pins[PinIndex]->Direction == EGPD_Input)
		{
			if (InputIndex == FoundInputs)
			{
				return Pins[PinIndex];
			}
			else
			{
				FoundInputs++;
			}
		}
	}

	return nullptr;
}

UEdGraphPin* UMHDialogGraphNode::GetOutputPin(int32 InputIndex) const
{
	check(InputIndex >= 0);

	for (int32 PinIndex = 0, FoundInputs = 0; PinIndex < Pins.Num(); PinIndex++)
	{
		if (Pins[PinIndex]->Direction == EGPD_Output)
		{
			if (InputIndex == FoundInputs)
			{
				return Pins[PinIndex];
			}
			else
			{
				FoundInputs++;
			}
		}
	}

	return nullptr;
}