// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "MHDialogNodeData.h"

#include "MHDialogNode.generated.h"

UCLASS(BlueprintType)
class UMHDialogNode : public UObject
{
	GENERATED_BODY()

  protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UMHDialogNode>> ChildNodes;

	UPROPERTY(BlueprintReadOnly)
	FMHDialogNodeData Data;

  public:
	const FMHDialogNodeData& GetData() const { return Data; }
	const TArray<TObjectPtr<UMHDialogNode>>& GetChildNodes() const { return ChildNodes; }

#if WITH_EDITORONLY_DATA

	friend class UMHDialogEditorSubsystem;

#endif
};