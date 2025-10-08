// created by MetalHeart

#pragma once
#include "Blueprint/UserWidget.h"
#include "Subtitles/SubtitlesAndClosedCaptionsDelegates.h"

#include "MHDialogUserWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS(BlueprintType, Blueprintable)
class UMHDialogUserWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
	DECLARE_DELEGATE_OneParam(FOnClickDelegate, UObject*);

	//~ Begin UUserWidget interface
  protected:
	virtual void NativeConstruct() override;
	//~End UUserWidget interface

  public:
	FOnClickDelegate OnClicked;

	UFUNCTION(BlueprintCallable)
	void SetPayload(UObject* InPayload);

	UFUNCTION(BlueprintCallable)
	void SetText(FText InText);

  protected:
	UFUNCTION()
	void HandleButtonClicked();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY()
	TObjectPtr<UObject> Payload;
};