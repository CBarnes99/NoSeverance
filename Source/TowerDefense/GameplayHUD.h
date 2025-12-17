#pragma once

#include "CombatPlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

UCLASS()
class TOWERDEFENSE_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	ACombatPlayerController* combatPlayerController;

	//UPROPERTY(VisibleDefaultsOnly)
	FInputModeGameOnly inputModeGameOnly;

	UFUNCTION(BlueprintCallable)
	void SetFocusToGame();

};
