#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UCore_GameInstance;

DECLARE_DELEGATE_OneParam(FOpenLevelSigniture, int /*Level Index*/)

UCLASS(Abstract)
class NOSEVERANCE_API UHUDMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Gets the level from GameMode_MainMenu */
	FOpenLevelSigniture OpenLevelEvent;

	UFUNCTION(BlueprintCallable)
	void IsLevelButtonUnlocked();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* LevelOneButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* LevelTwoButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* LevelThreeButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* ReturnButton;


protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	UCore_GameInstance* coreGameInstance;

	UPROPERTY(VisibleAnywhere)
	TArray<UButton*> levelButtons;

	UFUNCTION(BlueprintCallable)
	void PlayButtonFunction();

	UFUNCTION(BlueprintCallable)
	void QuitGameFunction();

	UFUNCTION(BlueprintCallable)
	void LevelOneButtonFunction();

	UFUNCTION(BlueprintCallable)
	void LevelTwoButtonFunction();

	UFUNCTION(BlueprintCallable)
	void LevelThreeButtonFunction();

	UFUNCTION(BlueprintCallable)
	void LevelButtonPressed(int level);

	UFUNCTION(BlueprintCallable)
	void ReturnButtonFunction();
};
