// created by MetalHeart

#include "Components/MHWidgetCloudComponent.h"

#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"

UMHWidgetCloudComponent::UMHWidgetCloudComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMHWidgetCloudComponent::Init(AActor* Owner, const FMHWidgetCloudComponentConfig& InConfig)
{
	Config			   = InConfig;
	TimelineComponent  = NewObject<UTimelineComponent>(Owner, NAME_None);

	UCurveFloat* Curve = NewObject<UCurveFloat>(this);
	Curve->FloatCurve  = *Config.PopUpAnimationCurve.GetRichCurve();

	TimelineComponent->AddInterpFloat(Curve, FOnTimelineFloatStatic::CreateUObject(this, &UMHWidgetCloudComponent::AnimatePosition));
	TimelineComponent->SetTimelineLength(Config.PopUpAnimationCurve.GetRichCurve()->GetLastKey().Time);
	TimelineComponent->RegisterComponent();
}

void UMHWidgetCloudComponent::OnHide(FSimpleDelegate&& Callback)
{
	OnHideCallback = MoveTemp(Callback);
}

UWidgetComponent* UMHWidgetCloudComponent::GetOrCreateDialogWidgetComponent(AActor* Owner, int32 Index)
{
	while (WidgetComponents.Num() <= Index)
	{
		WidgetComponents.Add(CreateWidgetComponent(Owner));
	}
	return WidgetComponents[Index];
}

void UMHWidgetCloudComponent::PlayShowAnimation()
{
	TimelineComponent->Play();
}

void UMHWidgetCloudComponent::PlayHideAnimation()
{
	TimelineComponent->Reverse();
}

void UMHWidgetCloudComponent::ResetWidgetsPositionAcrossSphere(AActor* Owner, const int32 WidgetCount)
{
	int32 Index = 0;

	// setup widgets in use
	for (; Index < WidgetCount; ++Index)
	{
		FVector PositionOnShere			  = GetPositionOnSphere(Index, WidgetCount);
		UWidgetComponent* WidgetComponent = GetOrCreateDialogWidgetComponent(Owner, Index);
		WidgetComponent->SetActive(true);
		WidgetComponent->SetRelativeLocation(PositionOnShere);
	}

	// hide unused widgets
	for (; Index < WidgetComponents.Num(); ++Index)
	{
		WidgetComponents[Index]->SetVisibility(false);
		WidgetComponents[Index]->SetActive(false);
	}
}

void UMHWidgetCloudComponent::RotateToTarget(const float DeltaTime, const FVector& TargetForward, const FVector& TargetLocation)
{
	// face component to target
	const FVector Start	   = GetComponentLocation();
	const FRotator Rotator = FRotationMatrix::MakeFromX(TargetLocation - Start).Rotator();
	SetWorldRotation(Rotator);

	// find delta by target forward vector
	const float ProjectionToZ = FVector::DotProduct(TargetForward, GetUpVector());
	const float ProjectionToY = FVector::DotProduct(TargetForward, GetRightVector());
	const float DeltaZ		  = FMath::Clamp(Config.RotationSpeed * DeltaTime * ProjectionToZ,	//
										 -Config.RotationMaxDelta,
										 Config.RotationMaxDelta);
	const float DeltaY		  = FMath::Clamp(Config.RotationSpeed * DeltaTime * ProjectionToY * -1,	 //
										 -Config.RotationMaxDelta,
										 Config.RotationMaxDelta);

	for (UWidgetComponent* WidgetComponent : WidgetComponents)
	{
		// rotate by delta
		WidgetComponent->SetRelativeLocation(WidgetComponent->GetRelativeLocation()
												 .RotateAngleAxis(DeltaZ, FVector::RightVector)
												 .RotateAngleAxis(DeltaY, FVector::UpVector));

		// then face to player
		const FRotator NewRotator = FRotationMatrix::MakeFromX(TargetLocation - WidgetComponent->GetComponentLocation()).Rotator();
		WidgetComponent->SetWorldRotation(NewRotator);
	}
}

void UMHWidgetCloudComponent::AnimatePosition(float Alpha)
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

	for (UWidgetComponent* WidgetComponent : WidgetComponents)
	{
		if (!WidgetComponent->IsActive())
		{
			continue;
		}

		if (FMath::IsNearlyZero(Alpha))
		{
			WidgetComponent->SetVisibility(false);
			continue;
		}

		WidgetComponent->SetVisibility(true);

		FVector Location = WidgetComponent->GetRelativeLocation();
		Location.Normalize();
		WidgetComponent->SetRelativeLocation(Location * Config.Radius * FMath::Max(Alpha, 0.001f));
		WidgetComponent->SetRelativeScale3D(FVector::OneVector * Config.WidgetScale * Alpha);
	}
}

UWidgetComponent* UMHWidgetCloudComponent::CreateWidgetComponent(AActor* Owner)
{
	UWidgetComponent* WidgetComponent = NewObject<UWidgetComponent>(Owner, NAME_None);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetActive(false);

	WidgetComponent->RegisterComponent();
	WidgetComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	return WidgetComponent;
}

FVector UMHWidgetCloudComponent::GetPositionOnSphere(const int32 Index, const int32 Size) const
{
	const float Theta = FMath::Acos(1.0f - 2.0f * (Index + 0.5f) / Size);
	const float Phi	  = 2.0f * Index * UE_PI / UE_GOLDEN_RATIO;
	return FVector2d{Theta, Phi}.SphericalToUnitCartesian() * Config.Radius;
}
