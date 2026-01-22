#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPlayerDefeated.generated.h"

class UTextBlock;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDPlayerDefeated : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextTimer;

	FTimerHandle CountdownTimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartCountdown(int time);

	UFUNCTION(BlueprintCallable)
	void UpdateCountdownText();

	UFUNCTION(BlueprintCallable)
	void EndCountdown();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	int countdownTime;
};
