// created by MetalHeart

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"

#include "MHDialogFactory.generated.h"

/**
 *
 */
UCLASS()
class UMHDialogFactory final : public UFactory
{
	GENERATED_BODY()

  public:
	UMHDialogFactory(const FObjectInitializer& ObjectInitializer);

	//~ Begin UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class,  //
									  UObject* InParent,
									  FName Name,
									  EObjectFlags Flags,
									  UObject* Context,
									  FFeedbackContext* Warn) override;
	//~ End UFactory interface
};
