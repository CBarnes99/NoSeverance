#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.generated.h"

class UWidgetSwitcher;
class UCore_GameInstance;
class UHUDButton;

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
	UHUDButton* PlayButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* QuitGameButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* LevelOneButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* LevelTwoButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* LevelThreeButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* ReturnFromLevelSelectButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* DeleteSaveButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* ConfirmSaveDeleteButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* CancelSaveDeleteButton;


protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	UCore_GameInstance* coreGameInstance;

	UPROPERTY(VisibleAnywhere)
	TArray<UHUDButton*> levelButtons;

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

	UFUNCTION(BlueprintCallable)
	void DeleteSaveMenu();

	UFUNCTION(BlueprintCallable)
	void ConfirmDeleteSave();
};
