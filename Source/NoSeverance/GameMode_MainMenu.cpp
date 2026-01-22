#include "GameMode_MainMenu.h"
#include "HUDMainMenu.h"

void AGameMode_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	mainMenu = CreateWidget<UHUDMainMenu>(GetWorld(), mainMenuClass);
	mainMenu->AddToViewport(0);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	mainMenu->GetLevelReferenceEvent.BindUObject(this, &AGameMode_MainMenu::GetLevelForMainMenu);
}

TSoftObjectPtr<UWorld> AGameMode_MainMenu::GetLevelForMainMenu(int levelIndex)
{
	switch (levelIndex)
	{
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("GetLevelForMainMenu: Case 1 matched"));
		return levelOne;
		break;

	case 2:
		UE_LOG(LogTemp, Warning, TEXT("GetLevelForMainMenu: Case 2 matched"));
		return levelTwo;
		break;

	case 3:
		UE_LOG(LogTemp, Warning, TEXT("GetLevelForMainMenu: Case 3 matched"));
		return levelThree;
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("GetLevelForMainMenu: No level with index - %d, default switch statement called, returned null"), levelIndex);
		return TSoftObjectPtr<UWorld>();
		break;
	}
}
