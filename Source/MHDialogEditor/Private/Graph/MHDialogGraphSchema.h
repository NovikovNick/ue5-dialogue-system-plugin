// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"

#include "MHDialogGraphSchema.generated.h"

UCLASS()
class UMHDialogGraphSchema final : public UEdGraphSchema
{
	GENERATED_BODY()

  public:
	// Allowable PinType.PinCategory values
	static const FName PC_Default;

	//~ Begin UEdGraphSchema interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	//~ End UEdGraphSchema interface
};

USTRUCT()
struct FMHDialogGraphSchemaAction_NewNode final : public FEdGraphSchemaAction
{
	GENERATED_BODY()

	// Inherit the base class's constructors
	using FEdGraphSchemaAction::FEdGraphSchemaAction;

	//~Begin FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph,
										UEdGraphPin* FromPin,
										const FVector2f& Location,
										bool bSelectNewNode = true) override;
	//~End FEdGraphSchemaAction interface
};
