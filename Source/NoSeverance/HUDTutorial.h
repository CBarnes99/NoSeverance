#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDTutorial.generated.h"

class UHUDButton;

DECLARE_DELEGATE(FCloseTutorialSigniture)

UCLASS(Abstract)
class NOSEVERANCE_API UHUDTutorial : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** Bound within the Core_Hud to close the widget when called */
	FCloseTutorialSigniture CloseTutorialEvent;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDButton* closeButton;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();


};
