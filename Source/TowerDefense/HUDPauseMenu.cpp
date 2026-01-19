#include "HUDPauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHUDPauseMenu::NativeConstruct()
{
	ContinueButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::Continue);
	QuitButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::Quit);
}

void UHUDPauseMenu::Continue()
{
	UE_LOG(LogTemp, Display, TEXT("Continue: Continue Button Pressed"));
	ContinueButtonPressedEvent.ExecuteIfBound();
}

void UHUDPauseMenu::Quit()
{
	UE_LOG(LogTemp, Display, TEXT("Quit: Quit Button Pressed"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}