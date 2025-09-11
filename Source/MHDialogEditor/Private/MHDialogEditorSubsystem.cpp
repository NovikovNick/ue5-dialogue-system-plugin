// created by MetalHeart

#include "MHDialogEditorSubsystem.h"

#include "EdGraph/EdGraph.h"
#include "Graph/MHDialogGraphNode.h"
#include "Graph/MHDialogGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "MHDialog.h"
#include "MHDialogEditorLog.h"
#include "MHDialogNode.h"

void UMHDialogEditorSubsystem::InitAsset(UMHDialog* Asset) const
{
	if (!IsValid(Asset->Graph))
	{
		Asset->Graph = FBlueprintEditorUtils::CreateNewGraph(Asset,	 //
															 NAME_None,
															 UEdGraph::StaticClass(),
															 UMHDialogGraphSchema::StaticClass());
		Asset->Graph->GetSchema()->CreateDefaultNodesForGraph(*Asset->Graph);
	}
}

void UMHDialogEditorSubsystem::UpdateAsset(UMHDialog* Asset) const
{
	check(Asset);
	UEdGraph* Graph = Asset->Graph;
	check(Graph);

	TMap<FGuid, UMHDialogNode*> AssetNodeMap;

	// recreate all nodes
	Asset->Root = nullptr;
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		UMHDialogGraphNode* GraphNode = Cast<UMHDialogGraphNode>(Node);
		if (!IsValid(GraphNode))
		{
			continue;
		}
		UMHDialogNode* AssetNode = NewObject<UMHDialogNode>(Asset);
		AssetNode->Data			 = GraphNode->Data;

		if (GraphNode->bRootNode)
		{
			Asset->Root = AssetNode;
		}

		AssetNodeMap.Add(GraphNode->NodeGuid, AssetNode);
	}
	checkf(Asset->Root, TEXT("Invalid rebuild asset without root node"));

	// link all nodes
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		UMHDialogGraphNode* GraphNode = Cast<UMHDialogGraphNode>(Node);
		if (!IsValid(GraphNode))
		{
			continue;
		}
		UMHDialogNode* AssetNode = AssetNodeMap[GraphNode->NodeGuid];

		if (UEdGraphPin* OutputPin = GraphNode->GetOutputPin())
		{
			for (UEdGraphPin* InputPin : OutputPin->LinkedTo)
			{
				const FGuid& NextNodeId		  = InputPin->GetOwningNode()->NodeGuid;
				UMHDialogNode* AssetChildNode = AssetNodeMap[NextNodeId];
				AssetNode->ChildNodes.Add(AssetChildNode);
			}
		}
	}

	UE_LOG(LogMHDialogEditor, Display, TEXT("Dialog asset updated"));
}
