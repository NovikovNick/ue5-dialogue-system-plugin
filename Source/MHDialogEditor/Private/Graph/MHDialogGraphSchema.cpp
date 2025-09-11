// created by MetalHeart

#include "Graph/MHDialogGraphSchema.h"

#include "Graph/MHDialogGraphNode.h"

#define LOCTEXT_NAMESPACE "MHDialogGraphSchema"

const FName UMHDialogGraphSchema::PC_Default(TEXT("DialogPin"));

void UMHDialogGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UMHDialogGraphNode> NodeCreator(Graph);
	UMHDialogGraphNode* Node = NodeCreator.CreateNode(false);
	Node->MarkAsRoot();
	Node->SetNodeTitle(LOCTEXT("RootNodeTitle", "How're you doing?"));
	NodeCreator.Finalize();
}

void UMHDialogGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	{
		auto Action = MakeShared<FMHDialogGraphSchemaAction_NewNode>(LOCTEXT("NewNodeCategory", "Node"),	//
																	 LOCTEXT("NewNodeAction", "Add Node"),	//
																	 LOCTEXT("NewNodeAction_Tooltip", "Adds a dialog node"),
																	 /*InGrouping*/ 0);
		ContextMenuBuilder.AddAction(Action);
	}
}

const FPinConnectionResponse UMHDialogGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not nullptr for pins"));
	}

	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Only output pin can be connected to input pin"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

UEdGraphNode* FMHDialogGraphSchemaAction_NewNode::PerformAction(UEdGraph* ParentGraph,
																UEdGraphPin* FromPin,
																const FVector2f& Location,
																bool bSelectNewNode)
{
	FGraphNodeCreator<UMHDialogGraphNode> NodeCreator(*ParentGraph);
	const FScopedTransaction Transaction(LOCTEXT("NewNode", "Dialog Editor: New Node"));
	ParentGraph->Modify();

	UMHDialogGraphNode* Node = NodeCreator.CreateNode(/*bCreatedByUser*/ true);
	Node->SetPosition(Location);
	Node->SetNodeTitle(LOCTEXT("NewNodeTitle", "Fine"));
	NodeCreator.Finalize();

	if (FromPin)
	{
		FromPin->Modify();
		Node->AutowireNewNode(FromPin);
		ParentGraph->NotifyGraphChanged();
	}

	return Node;
}

#undef LOCTEXT_NAMESPACE
