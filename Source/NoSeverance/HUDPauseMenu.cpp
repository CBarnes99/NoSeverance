#include "HUDPauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "HUDPlayerControls.h"

void UHUDPauseMenu::NativeConstruct()
{
	ContinueButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::Continue);
	QuitButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::Quit);
	ControlsButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::OpenControls);

	playerControls->SetVisibility(ESlateVisibility::Collapsed);
}

void UHUDPauseMenu::Continue()
{
	UE_LOG(LogTemp, Display, TEXT("Continue: Continue Button Pressed"));
	ContinueButtonPressedEvent.ExecuteIfBound();
}

void UHUDPauseMenu::OpenControls()
{
	if (playerControls->GetVisibility() == ESlateVisibility::Visible)
	{
		playerControls->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		playerControls->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHUDPauseMenu::Quit()
{
	UE_LOG(LogTemp, Display, TEXT("Quit: Quit Button Pressed"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}