#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDTurretCost.generated.h"

class UTextBlock;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDTurretCost : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* turretCostText;

	UFUNCTION(BlueprintCallable)
	void SetTurretCost(int price);

	UFUNCTION(BlueprintCallable)
	void IsTurretPriceVisable(bool bIsVisable);

protected:

	virtual void NativeConstruct() override;
};
