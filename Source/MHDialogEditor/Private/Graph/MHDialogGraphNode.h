// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "MHDialogNodeData.h"

#include "MHDialogGraphNode.generated.h"

class UMHDialogEditorSubsystem;

UCLASS()
class UMHDialogGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

	friend UMHDialogEditorSubsystem;

	//~ Begin UEdGraphNode interface
  public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void AllocateDefaultPins() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual bool CanUserDeleteNode() const override;
	virtual bool CanDuplicateNode() const override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;
	//~ End UEdGraphNode interface

	UEdGraphPin* GetInputPin(int32 InputIndex = 0) const;
	UEdGraphPin* GetOutputPin(int32 InputIndex = 0) const;

	void MarkAsRoot() { bRootNode = true; }
	void SetNodeTitle(FText Title);

  private:
	UPROPERTY()
	bool bRootNode = false;

	UPROPERTY(EditAnywhere)
	FMHDialogNodeData Data;
};
