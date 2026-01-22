#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPlayerControls.generated.h"

class UTextBlock;

UCLASS()
class TOWERDEFENSE_API UHUDPlayerControls : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* controlsText;

protected:

	virtual void NativeConstruct() override;

};
