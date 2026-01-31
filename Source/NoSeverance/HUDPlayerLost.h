#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPlayerLost.generated.h"

class UHUDButton;
class UWidgetAnimation;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDPlayerLost : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* MainMenuButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* RestartLevelButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* LostAnimation;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayLostAnimation();

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable)
	void RestartLevel();

};
