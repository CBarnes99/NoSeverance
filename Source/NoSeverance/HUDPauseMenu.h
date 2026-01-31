#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPauseMenu.generated.h"

class UHUDButton;
class UHUDPlayerControls;

DECLARE_DELEGATE(FContinueButtonPressedSigniture);
DECLARE_DELEGATE(FTutorialButtonPressedSigniture);

UCLASS(Abstract)
class NOSEVERANCE_API UHUDPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	//Both events are bound within Core_Hud
	FContinueButtonPressedSigniture ContinueButtonPressedEvent;
	FTutorialButtonPressedSigniture TutorialButtonPressedEvent;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* ContinueButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* ControlsButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* TutorialButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* RestartLevelButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* MainMenuButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDPlayerControls* playerControls;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Continue();

	UFUNCTION(BlueprintCallable)
	void OpenControls();

	UFUNCTION(BlueprintCallable)
	void Tutorial();

	UFUNCTION(BlueprintCallable)
	void RestartLevel();

	UFUNCTION(BlueprintCallable)
	void MainMenu();
	
};
