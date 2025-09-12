// created by MetalHeart

#pragma once

#include "EdGraph/EdGraph.h"

#include "MHDialogGraph.generated.h"

UCLASS()
class UMHDialogGraph : public UEdGraph
{
	GENERATED_BODY()

  public:
	bool IsLocked() const;
	void LockUpdates();
	void UnlockUpdates();

  private:
	bool bLockUpdates = false;
};
