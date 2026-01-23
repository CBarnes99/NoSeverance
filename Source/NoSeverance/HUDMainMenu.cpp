#include "HUDMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Core_GameInstance.h"

void UHUDMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnPressed.AddDynamic(this, &UHUDMainMenu::PlayButtonFunction);
	QuitGameButton->OnPressed.AddDynamic(this, &UHUDMainMenu::QuitGameFunction);
	LevelOneButton->OnPressed.AddDynamic(this, &UHUDMainMenu::LevelOneButtonFunction);
	LevelTwoButton->OnPressed.AddDynamic(this, &UHUDMainMenu::LevelTwoButtonFunction);
	LevelThreeButton->OnPressed.AddDynamic(this, &UHUDMainMenu::LevelThreeButtonFunction);
	ReturnButton->OnPressed.AddDynamic(this, &UHUDMainMenu::ReturnButtonFunction);

	levelButtons.Add(LevelOneButton);
	levelButtons.Add(LevelTwoButton);
	levelButtons.Add(LevelThreeButton);

}

void UHUDMainMenu::PlayButtonFunction()
{
	UE_LOG(LogTemp, Display, TEXT("PlayButtonFunction: Play Button pressed In Main Menu"));
	IsLevelButtonUnlocked();
	MenuSwitcher->SetActiveWidgetIndex(1);

}

void UHUDMainMenu::QuitGameFunction()
{
	UE_LOG(LogTemp, Display, TEXT("QuitGameFunction: Quit Game button pressed In Main Menu"));
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitPreference, true);
}

void UHUDMainMenu::ReturnButtonFunction()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UHUDMainMenu::IsLevelButtonUnlocked()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCore_GameInstance* coreGameInstance = Cast<UCore_GameInstance>(gameInstance);

	if (!coreGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("IsLevelButtonUnlocked: Core Game Instance Cast Failed within - %s"), *this->GetName());
		return;
	}

	for (int i = 0; i < levelButtons.Num(); i++)
	{
		if (coreGameInstance->IsLevelUnlocked(i + 1))
		{
			levelButtons[i]->SetIsEnabled(true);
		}
		else
		{
			levelButtons[i]->SetIsEnabled(false);
		}
	}
}

void UHUDMainMenu::LevelOneButtonFunction()
{
	LevelButtonPressed(1);
}

void UHUDMainMenu::LevelTwoButtonFunction()
{
	LevelButtonPressed(2);
}

void UHUDMainMenu::LevelThreeButtonFunction()
{
	LevelButtonPressed(3);
}

void UHUDMainMenu::LevelButtonPressed(int level)
{
	//TSoftObjectPtr<UWorld> levelRef;
	if (!OpenLevelEvent.IsBound())
	{
		UE_LOG(LogTemp, Error, TEXT("LevelButtonPressed: OpenLevelEvent NOT BOUND WITHIN - %s"), *this->GetName());
		return;
	}
	OpenLevelEvent.Execute(level);
}