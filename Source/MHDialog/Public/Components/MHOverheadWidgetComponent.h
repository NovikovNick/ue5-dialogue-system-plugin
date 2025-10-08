// created by MetalHeart

#pragma once

#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"

#include "MHOverheadWidgetComponent.generated.h"

class UWidgetComponent;
class UTimelineComponent;

USTRUCT(BlueprintType)
struct FMHOverheadWidgetComponentConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float Distance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	FVector Direction = FVector::UpVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float WidgetScale = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	FRuntimeFloatCurve PopUpAnimationCurve;
};

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UMHOverheadWidgetComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

  public:
	UMHOverheadWidgetComponent();

	void Init(AActor* Owner, const FMHOverheadWidgetComponentConfig& Config);
	void OnHide(FSimpleDelegate&& Callback);

	UWidgetComponent* GetWidgetComponent();
	void PlayShowAnimation();
	void PlayHideAnimation();

	void FaceToTarget(const FVector& TargetLocation);

  protected:
	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	FMHOverheadWidgetComponentConfig Config;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<UTimelineComponent> TimelineComponent;

  private:
	bool bTimelineReversing = false;
	FSimpleDelegate OnHideCallback;
	void AnimatePosition(float Alpha);
	UWidgetComponent* CreateWidgetComponent(AActor* Owner);
	UTimelineComponent* CreateTimelineComponent(AActor* Owner, FRichCurve* InPopUpAnimationCurve);
};
