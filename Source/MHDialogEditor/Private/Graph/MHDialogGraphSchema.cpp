// created by MetalHeart

#include "Graph/MHDialogGraphSchema.h"

#define LOCTEXT_NAMESPACE "MHDialogGraphSchema"

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

UEdGraphNode* FMHDialogGraphSchemaAction_NewNode::PerformAction(UEdGraph* ParentGraph,
																UEdGraphPin* FromPin,
																const FVector2f& Location,
																bool bSelectNewNode)
{
	FGraphNodeCreator<UEdGraphNode> NodeCreator(*ParentGraph);
	const FScopedTransaction Transaction(LOCTEXT("NewNode", "Dialog Editor: New Node"));
	ParentGraph->Modify();

	UEdGraphNode* Node = NodeCreator.CreateNode(/*bCreatedByUser*/ true);
	Node->SetPosition(Location);
	NodeCreator.Finalize();

	return Node;
}

#undef LOCTEXT_NAMESPACE
