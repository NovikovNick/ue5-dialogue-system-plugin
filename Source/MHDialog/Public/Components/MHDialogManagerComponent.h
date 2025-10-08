// created by MetalHeart

#pragma once

#include "Components/MHOverheadWidgetComponent.h"
#include "Components/MHWidgetCloudComponent.h"
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"

#include "MHDialogManagerComponent.generated.h"

class ACharacter;
class UWidgetComponent;
class USphereComponent;
class UMHDialog;
class UMHDialogNode;
class UMHDialogUserWidget;
struct FHitResult;

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class MHDIALOG_API UMHDialogManagerComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	UMHDialogManagerComponent();

	//~ Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	//~ End UActorComponent interface

  protected:
	// In

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	TArray<TObjectPtr<UMHDialog>> DialogAssets;

	// Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	bool bDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	float TriggerVolumeRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	TSubclassOf<UMHDialogUserWidget> OptionWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	TSubclassOf<UMHDialogUserWidget> PhraseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	FMHWidgetCloudComponentConfig WidgetCloudConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
	FMHOverheadWidgetComponentConfig OverheadWidgetConfig;

	// State

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<UMHWidgetCloudComponent> WidgetCloudComponent;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<UMHOverheadWidgetComponent> OverheadWidgetComponent;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<USphereComponent> TriggerVolume;

	// Variable

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	TObjectPtr<ACharacter> LocalPlayer;

	UPROPERTY(BlueprintReadWrite, Category = Dialog)
	bool bIsPlayerNear = false;

	UFUNCTION()
	void HandleDialogOptionClicked(UObject* InPayload);

	UFUNCTION()
	void HandleDialogPhraseClicked(UObject* InPayload);

	UFUNCTION()
	void OnDialogTriggerEnter(UPrimitiveComponent* OverlappedComponent,
							  AActor* OtherActor,
							  UPrimitiveComponent* OtherComp,
							  int32 OtherBodyIndex,
							  bool bFromSweep,
							  const FHitResult& SweepResult);
	UFUNCTION()
	void OnDialogTriggerExit(UPrimitiveComponent* OverlappedComponent,
							 AActor* OtherActor,
							 UPrimitiveComponent* OtherComp,
							 int32 OtherBodyIndex);

  private:
	void InitDialogOptionWidget(UWorld* World, int32 OptionIndex, const FText& Text, UObject* Payload);

	void OnHidePhrase();
	void OnHideOptions();

	void SetupAllDialogs();
	void SetupOptions(const TArray<TObjectPtr<UMHDialogNode>>& Options);
	void SetupPhrase(UMHDialogNode* DialogNode);

	TObjectPtr<UMHDialogNode> CurrentDialogNode;
};
