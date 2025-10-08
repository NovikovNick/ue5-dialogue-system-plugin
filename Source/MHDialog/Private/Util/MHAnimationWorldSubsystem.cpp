// created by MetalHeart

#include "Util/MHAnimationWorldSubsystem.h"

#include "Curves/CurveFloat.h"

void UMHAnimationWorldSubsystem::FAnimation::Tick(float DeltaTime)
{
	AnimationPosition += DeltaTime * PlayRate;
	AnimationPosition = bReversed  //
							? FMath::Max(AnimationPosition, 0)
							: FMath::Min(AnimationPosition, Curve->GetLastKey().Time);

	const float Alpha = Curve->Eval(AnimationPosition);
	OnTick.ExecuteIfBound(Alpha);
}
bool UMHAnimationWorldSubsystem::FAnimation::IsFinished() const
{
	return bReversed ? AnimationPosition <= 0 : AnimationPosition >= Curve->GetLastKey().Time;
}

void UMHAnimationWorldSubsystem::Tick(float DeltaSeconds)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(MHAnimationsTick)

	// Reverse to easily remove completed anims during iteration
	for (int Index = ActiveAnimations.Num() - 1; Index >= 0; --Index)
	{
		FAnimation& Animation = ActiveAnimations[Index];

		Animation.Tick(DeltaSeconds);

		if (Animation.IsFinished())
		{
			Animation.OnFinish.ExecuteIfBound();
			ActiveAnimations.RemoveAtSwap(Index);
		}
	}
}

TStatId UMHAnimationWorldSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(MHAnimationWorldSubsystem, STATGROUP_Tickables);
}

void UMHAnimationWorldSubsystem::AddAnimation(FRichCurve* Curve,
											  float PlayRate,
											  const OnTickDelegate& OnTickCallback,
											  const OnFinishDelegate& OnFinishCallback)
{
	ActiveAnimations.Emplace(/*AnimationPosition*/ PlayRate < 0 ? Curve->GetLastKey().Time : 0.0f,	//
							 PlayRate,
							 /*bReversed*/ PlayRate < 0,
							 Curve,
							 OnTickCallback,
							 OnFinishCallback);
}
