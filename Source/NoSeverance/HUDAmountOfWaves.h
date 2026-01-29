#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDAmountOfWaves.generated.h"

class UTextBlock;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDAmountOfWaves : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* amountOfWavesText;

	UFUNCTION(BlueprintCallable)
	void SetMaxWave(int amount);

	UFUNCTION(BlueprintCallable)
	void UpdateText();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	int lastWave;

	UPROPERTY(VisibleAnywhere)
	int currentWave;
};
