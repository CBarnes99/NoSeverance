#include "GameplayHUD.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	combatPlayerController = Cast<ACombatPlayerController>(playerController);
	SetFocusToGame();
	
}

void AGameplayHUD::SetFocusToGame()
{
	combatPlayerController->SetInputMode(inputModeGameOnly);
}
