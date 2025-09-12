// created by MetalHeart

#include "Graph/MHDialogGraph.h"

bool UMHDialogGraph::IsLocked() const
{
	return bLockUpdates;
}

void UMHDialogGraph::LockUpdates()
{
	bLockUpdates = true;
}

void UMHDialogGraph::UnlockUpdates()
{
	bLockUpdates = false;
	NotifyGraphChanged();
}
