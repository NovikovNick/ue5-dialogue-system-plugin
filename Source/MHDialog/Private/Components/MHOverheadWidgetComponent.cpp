// created by MetalHeart

#include "Components/MHOverheadWidgetComponent.h"

#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"

UMHOverheadWidgetComponent::UMHOverheadWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMHOverheadWidgetComponent::Init(AActor* Owner, const FMHOverheadWidgetComponentConfig& InConfig)
{
	check(Owner);
	Config			  = InConfig;
	WidgetComponent	  = CreateWidgetComponent(Owner);
	TimelineComponent = CreateTimelineComponent(Owner, Config.PopUpAnimationCurve.GetRichCurve());
}
void UMHOverheadWidgetComponent::OnHide(FSimpleDelegate&& Callback)
{
	OnHideCallback = MoveTemp(Callback);
}

UWidgetComponent* UMHOverheadWidgetComponent::GetWidgetComponent()
{
	return WidgetComponent;
}

void UMHOverheadWidgetComponent::PlayShowAnimation()
{
	TimelineComponent->Play();
}

void UMHOverheadWidgetComponent::PlayHideAnimation()
{
	TimelineComponent->Reverse();
}

void UMHOverheadWidgetComponent::FaceToTarget(const FVector& TargetLocation)
{
	const FRotator NewRotator = FRotationMatrix::MakeFromX(TargetLocation - WidgetComponent->GetComponentLocation()).Rotator();
	WidgetComponent->SetWorldRotation(NewRotator);
}

void UMHOverheadWidgetComponent::AnimatePosition(float Alpha)
{
	// As for me it looks like a bug that the timeline component is marked as not playing
	// for the last call of tick callback. But we have what we have, and it forces us
	// to use hacks like these to fire event on the animation's completion when playing backwards.
	if (!TimelineComponent->IsPlaying())
	{
		if (bTimelineReversing)
		{
			OnHideCallback.ExecuteIfBound();
		}
	}
	else
	{
		bTimelineReversing = TimelineComponent->IsReversing();
	}

	if (FMath::IsNearlyZero(Alpha))
	{
		WidgetComponent->SetVisibility(false);
		return;
	}

	WidgetComponent->SetVisibility(true);

	FVector Location = Config.Direction;
	Location.Normalize();
	Location *= Config.Distance * Alpha;
	WidgetComponent->SetRelativeLocation(Location);
	WidgetComponent->SetRelativeScale3D(FVector::OneVector * Config.WidgetScale * Alpha);
}

UWidgetComponent* UMHOverheadWidgetComponent::CreateWidgetComponent(AActor* Owner)
{
	UWidgetComponent* Widget = NewObject<UWidgetComponent>(Owner, NAME_None);
	Widget->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Widget->SetDrawAtDesiredSize(true);
	Widget->SetVisibility(false);
	Widget->SetActive(false);

	Widget->RegisterComponent();
	Widget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	return Widget;
}

UTimelineComponent* UMHOverheadWidgetComponent::CreateTimelineComponent(AActor* Owner, FRichCurve* InPopUpAnimationCurve)
{
	check(Owner);
	check(InPopUpAnimationCurve);

	UTimelineComponent* Timeline	 = NewObject<UTimelineComponent>(Owner, NAME_None);

	UCurveFloat* PopUpAnimationCurve = NewObject<UCurveFloat>(Owner);
	PopUpAnimationCurve->FloatCurve	 = *InPopUpAnimationCurve;
	Timeline->AddInterpFloat(PopUpAnimationCurve,
							 FOnTimelineFloatStatic::CreateUObject(this, &UMHOverheadWidgetComponent::AnimatePosition));

	Timeline->RegisterComponent();
	return Timeline;
}
