#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDVictoryScreen.generated.h"

class UButton;
class UWidgetAnimation;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDVictoryScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget));
	UButton* MainMenuButton;

	//UPROPERTY(EditDefaultsOnly, meta = (BindWidget));
	//UButton* NextRoundButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* VictoryAnimation;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayVictoryAnimation();

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnMainMenuButtonPressed();

	UFUNCTION(BlueprintCallable)
	void OnNextRoundButtonPressed();

};
