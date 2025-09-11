// created by MetalHeart

#pragma once

#include "CoreMinimal.h"

#include "MHDialogNodeData.generated.h"

USTRUCT(BlueprintType)
struct FMHDialogNodeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
	float ReadDurationSec = 3.0f;
};
