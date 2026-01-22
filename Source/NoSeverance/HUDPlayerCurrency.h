#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPlayerCurrency.generated.h"

class UTextBlock;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDPlayerCurrency : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* CurrencyText;

	UFUNCTION(BlueprintCallable)
	void SetTextToPlayerCurrency(int amount);
};
