#include "HUDPauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "HUDPlayerControls.h"

void UHUDPauseMenu::NativeConstruct()
{
	ContinueButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::Continue);
	MainMenuButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::MainMenu);
	ControlsButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::OpenControls);
	TutorialButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::Tutorial);
	RestartLevelButton->OnClicked.AddDynamic(this, &UHUDPauseMenu::RestartLevel);

	playerControls->SetVisibility(ESlateVisibility::Collapsed);
}

void UHUDPauseMenu::Continue()
{
	UE_LOG(LogTemp, Display, TEXT("Continue: Continue Button Pressed"));
	ContinueButtonPressedEvent.ExecuteIfBound();
}

void UHUDPauseMenu::OpenControls()
{
	UE_LOG(LogTemp, Display, TEXT("OpenControls: Open Controls Button Pressed"));

	if (playerControls->GetVisibility() == ESlateVisibility::Visible)
	{
		playerControls->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		playerControls->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHUDPauseMenu::Tutorial()
{
	UE_LOG(LogTemp, Display, TEXT("Tutorial: Tutorial Button Pressed"));
	TutorialButtonPressedEvent.ExecuteIfBound();
}

void UHUDPauseMenu::RestartLevel()
{
	UE_LOG(LogTemp, Display, TEXT("RestartLevel: Restart Level Button Pressed"));
	FString currentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	UGameplayStatics::OpenLevel(GetWorld(), FName(currentLevelName));
}

void UHUDPauseMenu::MainMenu()
{
	UE_LOG(LogTemp, Display, TEXT("MainMenu: MainMenu Button Pressed"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}