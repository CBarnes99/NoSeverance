#include "HUDVictoryScreen.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHUDVictoryScreen::NativeConstruct()
{
	MainMenuButton->OnPressed.AddDynamic(this, &UHUDVictoryScreen::OnMainMenuButtonPressed);
	NextRoundButton->OnPressed.AddDynamic(this, &UHUDVictoryScreen::OnNextRoundButtonPressed);
}

void UHUDVictoryScreen::OnMainMenuButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("OnMainMenuButtonPressed: BUTTON PRESSED!!"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

void UHUDVictoryScreen::OnNextRoundButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("OnNextRoundButtonPressed: BUTTON PRESSED!!"));
}

void UHUDVictoryScreen::PlayVictoryAnimation()
{
	if (!VictoryAnimation)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayVictoryAnimation: VICTORY ANIMATION NOT SET WITHIN - %s"), *this->GetName());
		return;
	}

	PlayAnimation(VictoryAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
}