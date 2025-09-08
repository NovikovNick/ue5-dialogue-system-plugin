// created by MetalHeart

#pragma once

#include "AssetDefinitionDefault.h"

#include "AssetDefinition_MHDialog.generated.h"

UCLASS()
class UAssetDefinition_MHDialog : public UAssetDefinitionDefault
{
	GENERATED_BODY()

  protected:
	//~ Begin UAssetDefinition interface
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
	//~ End UAssetDefinition interface
};