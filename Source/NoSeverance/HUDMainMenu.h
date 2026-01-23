#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.generated.h"

class UButton;
class UWidgetSwitcher;

DECLARE_DELEGATE_RetVal_OneParam(TSoftObjectPtr<UWorld>, /*Level Reference*/ FGetLevelReferenceSigniture, int /*Level Index From GameMode_MainMenu*/)

UCLASS(Abstract)
class NOSEVERANCE_API UHUDMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Gets the level from GameMode_MainMenu */
	FGetLevelReferenceSigniture GetLevelReferenceEvent;

	UFUNCTION(BlueprintCallable)
	void IsLevelButtonUnlocked(UButton* levelButton, bool bIsUnlocked);

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
	void ReturnButtonFunction();

	UFUNCTION(BlueprintCallable)
	void OpenLevelFromSoftObjectPtrAsync(TSoftObjectPtr<UWorld>& levelReference);

	void OpenLevelBySoftObject(TSoftObjectPtr<UWorld> LevelReference);

};
