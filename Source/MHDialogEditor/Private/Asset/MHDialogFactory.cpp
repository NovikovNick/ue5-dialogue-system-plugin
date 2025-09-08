// created by MetalHeart

#include "Asset/MHDialogFactory.h"

#include "MHDialog.h"

UMHDialogFactory::UMHDialogFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew	   = true;
	bEditAfterNew  = true;
	SupportedClass = UMHDialog::StaticClass();
}

UObject* UMHDialogFactory::FactoryCreateNew(UClass* Class,	//
											UObject* InParent,
											FName Name,
											EObjectFlags Flags,
											UObject* Context,
											FFeedbackContext* Warn)
{
	return NewObject<UMHDialog>(InParent, Name, Flags);
}
