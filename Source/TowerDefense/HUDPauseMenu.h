#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPauseMenu.generated.h"

class UButton;
class UHUDPlayerControls;

DECLARE_DELEGATE(FContinueButtonPressedSigniture);

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	FContinueButtonPressedSigniture ContinueButtonPressedEvent;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* ContinueButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* ControlsButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDPlayerControls* playerControls;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Continue();

	UFUNCTION(BlueprintCallable)
	void OpenControls();

	UFUNCTION(BlueprintCallable)
	void Quit();
	
};
