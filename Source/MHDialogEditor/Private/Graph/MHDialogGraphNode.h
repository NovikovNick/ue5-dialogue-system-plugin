// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"

#include "MHDialogGraphNode.generated.h"

UCLASS()
class UMHDialogGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

	//~ Begin UEdGraphNode interface
  public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void AllocateDefaultPins() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	//~ End UEdGraphNode interface

  private:
	UEdGraphPin* GetInputPin(int32 InputIndex = 0) const;
	UEdGraphPin* GetOutputPin(int32 InputIndex = 0) const;

  public:
	UPROPERTY()
	bool bRootNode = false;
};
