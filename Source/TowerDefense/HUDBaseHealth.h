#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDBaseHealth.generated.h"

class UTextBlock;

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDBaseHealth : public UUserWidget
{ 
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* baseHealthText;

	UFUNCTION(BlueprintCallable)
	void UpdateBaseHealthHUD(int healthValue);

};
