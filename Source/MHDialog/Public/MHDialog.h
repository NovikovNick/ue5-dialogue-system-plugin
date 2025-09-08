// created by MetalHeart

#pragma once

#include "CoreMinimal.h"

#include "MHDialog.generated.h"

UCLASS()
class MHDIALOG_API UMHDialog : public UObject
{
	GENERATED_BODY()
  public:
	FText Topic = NSLOCTEXT("UMHDialog", "DefaultTopic", "Topic");
};