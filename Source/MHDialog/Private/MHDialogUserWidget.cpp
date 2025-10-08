// created by MetalHeart

#include "UI/MHDialogUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMHDialogUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UMHDialogUserWidget::HandleButtonClicked);
}

void UMHDialogUserWidget::SetPayload(UObject* InPayload)
{
	Payload = InPayload;
}

void UMHDialogUserWidget::SetText(FText InText)
{
	TextBlock->SetText(InText);
}

void UMHDialogUserWidget::HandleButtonClicked()
{
	OnClicked.Execute(Payload);
}
