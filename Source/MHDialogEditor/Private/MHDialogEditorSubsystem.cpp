// created by MetalHeart

#include "MHDialogEditorSubsystem.h"

#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "MHDialog.h"

void UMHDialogEditorSubsystem::InitAsset(UMHDialog* Asset) const
{
	if (!IsValid(Asset->Graph))
	{
		Asset->Graph = FBlueprintEditorUtils::CreateNewGraph(Asset,	 //
															 NAME_None,
															 UEdGraph::StaticClass(),
															 UEdGraphSchema::StaticClass());
		Asset->Graph->GetSchema()->CreateDefaultNodesForGraph(*Asset->Graph);
	}
}
