#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDAmountOfEnemiesInWave.generated.h"

class UTextBlock;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDAmountOfEnemiesInWave : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* amountOfEnemiesText;

	UFUNCTION(BlueprintCallable)
	void SetMaxAmountOfEnemiesText(int amount);

	UFUNCTION(BlueprintCallable)
	void UpdateText();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	int maxEnemiesInWave;

	UPROPERTY(VisibleAnywhere)
	int currentEnemiesInWave;
};
