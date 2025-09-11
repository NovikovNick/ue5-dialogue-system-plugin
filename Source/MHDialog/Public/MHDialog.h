// created by MetalHeart

#pragma once

#include "CoreMinimal.h"

#include "MHDialog.generated.h"

class UMHDialogNode;

UCLASS(BlueprintType)
class MHDIALOG_API UMHDialog : public UObject
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Topic = NSLOCTEXT("UMHDialog", "DefaultTopic", "Topic");

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMHDialogNode> Root;

  public:
	FText GetTopic() const { return Topic; }

#if WITH_EDITORONLY_DATA

	friend class UMHDialogEditorSubsystem;

	/** Graph for editor*/
	UPROPERTY()
	TObjectPtr<class UEdGraph> Graph;

#endif
};