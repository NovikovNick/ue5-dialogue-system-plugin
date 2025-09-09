// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"

#include "MHDialogEditorSubsystem.generated.h"

class UMHDialog;

/**
 * The subsystem is meant to hold any editor operations that are not UI related (those are
 * handled by the toolkit)
 */
UCLASS()
class UMHDialogEditorSubsystem final : public UEditorSubsystem
{
	GENERATED_BODY()

  public:
	void InitAsset(UMHDialog* Asset) const;
};