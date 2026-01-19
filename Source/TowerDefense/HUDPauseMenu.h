#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPauseMenu.generated.h"

class UButton;

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
	UButton* QuitButton;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Continue();

	UFUNCTION(BlueprintCallable)
	void Quit();
	
};
