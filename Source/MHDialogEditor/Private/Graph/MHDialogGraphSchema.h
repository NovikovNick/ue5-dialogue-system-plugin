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
	//~ Begin UEdGraphSchema interface
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
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
