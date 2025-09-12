// created by MetalHeart

#include "Graph/MHDialogGraphSchema.h"

#include "AIGraphConnectionDrawingPolicy.h"
#include "AIGraphSchema.h"
#include "Framework/Commands/GenericCommands.h"
#include "Graph/MHDialogGraph.h"
#include "Graph/MHDialogGraphNode.h"
#include "GraphEditorActions.h"

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

void UMHDialogGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (!Context->Node)
	{
		return;
	}

	{  // General actions
		FToolMenuSection& Section = Menu->AddSection(TEXT("NodeActions"));
		Section.AddMenuEntry(FGenericCommands::Get().SelectAll);
		Section.AddMenuEntry(FGenericCommands::Get().Delete);
		Section.AddMenuEntry(FGenericCommands::Get().Copy);
		Section.AddMenuEntry(FGenericCommands::Get().Cut);
		Section.AddMenuEntry(FGenericCommands::Get().Paste);
		Section.AddMenuEntry(FGenericCommands::Get().Duplicate);
	}
	{  // Graph Editor actions
		FToolMenuSection& Section = Menu->AddSection("Editor");
		Section.AddMenuEntry(FGraphEditorCommands::Get().CreateComment);
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

TSharedPtr<FEdGraphSchemaAction> UMHDialogGraphSchema::GetCreateCommentAction() const
{
	return TSharedPtr<FEdGraphSchemaAction>(static_cast<FEdGraphSchemaAction*>(new FAISchemaAction_AddComment));
}

FConnectionDrawingPolicy* UMHDialogGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID,
																			  int32 InFrontLayerID,
																			  float InZoomFactor,
																			  const FSlateRect& InClippingRect,
																			  class FSlateWindowElementList& InDrawElements,
																			  class UEdGraph* InGraphObj) const
{
	return new FAIGraphConnectionDrawingPolicy(InBackLayerID,  //
											   InFrontLayerID,
											   InZoomFactor,
											   InClippingRect,
											   InDrawElements,
											   InGraphObj);
}

UEdGraphNode* FMHDialogGraphSchemaAction_NewNode::PerformAction(UEdGraph* ParentGraph,
																UEdGraphPin* FromPin,
																const FVector2f& Location,
																bool bSelectNewNode)
{
	UMHDialogGraph* DialogGraph = CastChecked<UMHDialogGraph>(ParentGraph);
	DialogGraph->LockUpdates();

	FGraphNodeCreator<UMHDialogGraphNode> NodeCreator(*DialogGraph);
	const FScopedTransaction Transaction(LOCTEXT("NewNode", "Dialog Editor: New Node"));
	DialogGraph->Modify();

	UMHDialogGraphNode* Node = NodeCreator.CreateNode(/*bCreatedByUser*/ true);
	Node->SetPosition(Location);
	Node->SetNodeTitle(LOCTEXT("NewNodeTitle", "Fine"));
	NodeCreator.Finalize();

	if (FromPin)
	{
		FromPin->Modify();
		Node->AutowireNewNode(FromPin);
		DialogGraph->NotifyGraphChanged();
	}

	DialogGraph->UnlockUpdates();
	return Node;
}

#undef LOCTEXT_NAMESPACE
