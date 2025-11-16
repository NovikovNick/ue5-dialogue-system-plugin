// created by MetalHeart

#pragma once

#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"

#include "MHWidgetCloudComponent.generated.h"

class UWidgetComponent;
class UTimelineComponent;

USTRUCT(BlueprintType)
struct FMHWidgetCloudComponentConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float Radius = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float RotationSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float RotationMaxDelta = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float WidgetScale = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	FRuntimeFloatCurve PopUpAnimationCurve;
};

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UMHWidgetCloudComponent : public USceneComponent
{
	GENERATED_BODY()

  public:
	UMHWidgetCloudComponent();

	void Init(AActor* Owner, const FMHWidgetCloudComponentConfig& Config);
	void OnHide(FSimpleDelegate&& Callback);

	UWidgetComponent* GetOrCreateDialogWidgetComponent(AActor* Owner, int32 Index);
	void PlayShowAnimation();
	void PlayHideAnimation();

	void ResetWidgetsPositionAcrossSphere(AActor* Owner, int32 WidgetCount);
	void RotateToTarget(float DeltaTime, const FVector& TargetForward, const FVector& TargetLocation);

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	FMHWidgetCloudComponentConfig Config;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TArray<TObjectPtr<UWidgetComponent>> WidgetComponents;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<UTimelineComponent> TimelineComponent;

  private:
	bool bTimelineReversing = false;
	FSimpleDelegate OnHideCallback;
	void AnimatePosition(float Alpha);
	UWidgetComponent* CreateWidgetComponent(AActor* Owner);
	FVector GetPositionOnSphere(int32 Index, int32 Size) const;
};
