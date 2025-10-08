// created by MetalHeart

#pragma once

#include "CoreMinimal.h"

#include "MHAnimationWorldSubsystem.generated.h"

struct FRichCurve;

UCLASS()
class UMHAnimationWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

  public:
	DECLARE_DELEGATE_OneParam(OnTickDelegate, float);
	DECLARE_DELEGATE(OnFinishDelegate);

	struct FAnimation
	{

		float AnimationPosition = 0.0f;
		float PlayRate			= 1.0f;
		bool bReversed			= false;

		FRichCurve* Curve;
		OnTickDelegate OnTick;
		OnFinishDelegate OnFinish;

		void Tick(float DeltaTime);

		bool IsFinished() const;
	};

	TArray<FAnimation> ActiveAnimations;

	//~ Begin UTickableWorldSubsystem interface
	virtual void Tick(float DeltaSeconds) override;
	virtual TStatId GetStatId() const override;
	//~ End UTickableWorldSubsystem interface

	void AddAnimation(FRichCurve* Curve,
					  float PlayRate,
					  const OnTickDelegate& OnTickCallback,
					  const OnFinishDelegate& OnFinishCallback = {});
};
