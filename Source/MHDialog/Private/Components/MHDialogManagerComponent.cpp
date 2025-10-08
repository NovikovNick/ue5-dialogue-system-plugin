// created by MetalHeart

#include "Components/MHDialogManagerComponent.h"

#include "Components/MHWidgetCloudComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MHDialog.h"
#include "MHDialogLog.h"
#include "MHDialogNode.h"
#include "UI/MHDialogUserWidget.h"

UMHDialogManagerComponent::UMHDialogManagerComponent()
{
	bAutoActivate					  = true;
	PrimaryComponentTick.bCanEverTick = true;
	WidgetCloudConfig.PopUpAnimationCurve.GetRichCurve()->AddKey(0.f, 0.f);
	WidgetCloudConfig.PopUpAnimationCurve.GetRichCurve()->AddKey(1.f, 1.f);
	OverheadWidgetConfig.PopUpAnimationCurve.GetRichCurve()->AddKey(0.f, 0.f);
	OverheadWidgetConfig.PopUpAnimationCurve.GetRichCurve()->AddKey(1.f, 1.f);
}

void UMHDialogManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	{
		TriggerVolume = NewObject<USphereComponent>(GetOwner(), NAME_None, RF_Transient);
		TriggerVolume->InitSphereRadius(TriggerVolumeRadius);
		TriggerVolume->SetHiddenInGame(!bDebug);
		TriggerVolume->SetGenerateOverlapEvents(true);
		TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &UMHDialogManagerComponent::OnDialogTriggerEnter);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &UMHDialogManagerComponent::OnDialogTriggerExit);

		TriggerVolume->RegisterComponent();
		TriggerVolume->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		TriggerVolume->SetRelativeLocation(FVector::ZeroVector);
	}

	{
		checkf(!OverheadWidgetConfig.PopUpAnimationCurve.GetRichCurve()->IsEmpty(),
			   TEXT("OverheadWidget's animation curve shouldn't be empty"));
		OverheadWidgetComponent = NewObject<UMHOverheadWidgetComponent>(GetOwner(), NAME_None, RF_Transient);
		OverheadWidgetComponent->Init(GetOwner(), OverheadWidgetConfig);
		OverheadWidgetComponent->OnHide(FSimpleDelegate::CreateUObject(this, &UMHDialogManagerComponent::OnHidePhrase));

		UMHDialogUserWidget* Widget = Cast<UMHDialogUserWidget>(CreateWidget(World, PhraseWidgetClass));
		Widget->OnClicked =
			UMHDialogUserWidget::FOnClickDelegate::CreateUObject(this, &UMHDialogManagerComponent::HandleDialogPhraseClicked);
		OverheadWidgetComponent->GetWidgetComponent()->SetWidget(Widget);

		OverheadWidgetComponent->RegisterComponent();
		OverheadWidgetComponent->AttachToComponent(TriggerVolume, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		OverheadWidgetComponent->SetRelativeLocation(FVector::ZeroVector);
	}

	{
		checkf(!WidgetCloudConfig.PopUpAnimationCurve.GetRichCurve()->IsEmpty(),
			   TEXT("WidgetCloudConfig's animation curve shouldn't be empty"));
		WidgetCloudComponent = NewObject<UMHWidgetCloudComponent>(GetOwner(), NAME_None, RF_Transient);
		WidgetCloudComponent->Init(GetOwner(), WidgetCloudConfig);
		WidgetCloudComponent->OnHide(FSimpleDelegate::CreateUObject(this, &UMHDialogManagerComponent::OnHideOptions));

		WidgetCloudComponent->RegisterComponent();
		WidgetCloudComponent->AttachToComponent(TriggerVolume, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		WidgetCloudComponent->SetRelativeLocation(FVector::ZeroVector);
	}

	LocalPlayer = UGameplayStatics::GetPlayerCharacter(World, 0);
}

void UMHDialogManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsPlayerNear)
	{
		APlayerController* PlayerController = Cast<APlayerController>(LocalPlayer->GetController());
		if (IsValid(PlayerController))
		{
			FVector Location = PlayerController->PlayerCameraManager->GetCameraLocation();
			FVector Forward	 = PlayerController->PlayerCameraManager->GetActorForwardVector();

			OverheadWidgetComponent->FaceToTarget(Location);
			WidgetCloudComponent->RotateToTarget(DeltaTime, Forward, Location);
		}
	}
}

void UMHDialogManagerComponent::OnDialogTriggerEnter(UPrimitiveComponent* OverlappedComponent,
													 AActor* OtherActor,
													 UPrimitiveComponent* OtherComp,
													 int32 OtherBodyIndex,
													 bool bFromSweep,
													 const FHitResult& SweepResult)
{
#if WITH_EDITOR
	const double T0 = FPlatformTime::Seconds();
#endif

	if (OtherActor != LocalPlayer)
	{
		return;
	}

	bIsPlayerNear = true;

	SetupAllDialogs();
	WidgetCloudComponent->PlayShowAnimation();

#if WITH_EDITOR
	const double T1 = FPlatformTime::Seconds();
	UE_LOG(LogMHDialog, Display, TEXT("%s: It takes %.02f sec to open dialog"), *GetOwner()->GetName(), T1 - T0);
#endif
}

void UMHDialogManagerComponent::OnDialogTriggerExit(UPrimitiveComponent* OverlappedComponent,
													AActor* OtherActor,
													UPrimitiveComponent* OtherComp,
													int32 OtherBodyIndex)
{
	if (OtherActor != LocalPlayer)
	{
		return;
	}

	bIsPlayerNear = false;
	WidgetCloudComponent->PlayHideAnimation();
	OverheadWidgetComponent->PlayHideAnimation();
}

void UMHDialogManagerComponent::HandleDialogOptionClicked(UObject* InPayload)
{
	if (UMHDialogNode* DialogNode = Cast<UMHDialogNode>(InPayload))
	{
		const TArray<TObjectPtr<UMHDialogNode>>& Answers = DialogNode->GetChildNodes();
		CurrentDialogNode								 = Answers.IsEmpty() ? nullptr : Answers[0];
	}
	else if (UMHDialog* DialogAsset = Cast<UMHDialog>(InPayload))
	{
		CurrentDialogNode = DialogAsset->GetRoot();
	}

	WidgetCloudComponent->PlayHideAnimation();
}

void UMHDialogManagerComponent::OnHideOptions()
{
	if (!bIsPlayerNear)
	{
		return;
	}

	if (CurrentDialogNode == nullptr)
	{
		SetupAllDialogs();
		WidgetCloudComponent->PlayShowAnimation();
		return;
	}

	// show phrase
	SetupPhrase(CurrentDialogNode);
	OverheadWidgetComponent->PlayShowAnimation();
}

void UMHDialogManagerComponent::HandleDialogPhraseClicked(UObject* InPayload)
{
	OverheadWidgetComponent->PlayHideAnimation();
}

void UMHDialogManagerComponent::OnHidePhrase()
{
	if (!bIsPlayerNear)
	{
		return;
	}

	if (CurrentDialogNode && !CurrentDialogNode->GetChildNodes().IsEmpty())
	{
		SetupOptions(CurrentDialogNode->GetChildNodes());
	}
	else
	{
		SetupAllDialogs();
	}

	WidgetCloudComponent->PlayShowAnimation();
}

void UMHDialogManagerComponent::InitDialogOptionWidget(UWorld* World, int32 OptionIndex, const FText& Text, UObject* Payload)
{
	check(World);

	UWidgetComponent* WidgetComponent = WidgetCloudComponent->GetOrCreateDialogWidgetComponent(GetOwner(), OptionIndex);
	UMHDialogUserWidget* Widget		  = Cast<UMHDialogUserWidget>(WidgetComponent->GetWidget());
	if (!Widget)
	{
		Widget = Cast<UMHDialogUserWidget>(CreateWidget(World, OptionWidgetClass));
		Widget->OnClicked =
			UMHDialogUserWidget::FOnClickDelegate::CreateUObject(this, &UMHDialogManagerComponent::HandleDialogOptionClicked);
		WidgetComponent->SetWidget(Widget);
	}
	Widget->SetText(Text);
	Widget->SetPayload(Payload);
}

void UMHDialogManagerComponent::SetupAllDialogs()
{
	for (int32 i = 0; i < DialogAssets.Num(); ++i)
	{
		InitDialogOptionWidget(GetWorld(), i, DialogAssets[i]->GetTopic(), DialogAssets[i]);
	}
	WidgetCloudComponent->ResetWidgetsPositionAcrossSphere(GetOwner(), DialogAssets.Num());
}

void UMHDialogManagerComponent::SetupOptions(const TArray<TObjectPtr<UMHDialogNode>>& Options)
{
	for (int32 i = 0; i < Options.Num(); ++i)
	{
		InitDialogOptionWidget(GetWorld(), i, Options[i]->GetData().Content, Options[i]);
	}
	WidgetCloudComponent->ResetWidgetsPositionAcrossSphere(GetOwner(), Options.Num());
}

void UMHDialogManagerComponent::SetupPhrase(UMHDialogNode* DialogNode)
{
	UWidgetComponent* WidgetComponent = OverheadWidgetComponent->GetWidgetComponent();
	WidgetComponent->SetActive(true);
	WidgetComponent->SetVisibility(true);
	UMHDialogUserWidget* Widget = Cast<UMHDialogUserWidget>(WidgetComponent->GetWidget());
	Widget->SetPayload(DialogNode);
	Widget->SetText(DialogNode->GetData().Content);
}
