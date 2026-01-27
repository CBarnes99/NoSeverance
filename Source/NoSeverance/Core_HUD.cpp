#include "Core_HUD.h"
#include "Kismet/GameplayStatics.h"

#include "HUDTurretSelectionMenu.h"
#include "HUDPlayerHud.h"
#include "HUDHealthAndMana.h"
#include "HUDWeaponTurretSelector.h"
#include "HUDVictoryScreen.h"
#include "HUDPlayerDefeated.h"
#include "HUDPlayerLost.h"
#include "HUDPauseMenu.h"
#include "HUDTutorial.h"
#include "ModalBaseClass.h"

#include "DA_TurretInfo.h"
#include "Core_PlayerController.h"
#include "PlayerCharacter.h"
#include "Core_GameMode.h"
#include "Core_GameState.h"

void ACore_HUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s has initilized!"), *this->GetName());

	localCorePlayerController = Cast<ACore_PlayerController>(GetOwningPlayerController());

	if (!localCorePlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: PLAYER CONTROLLER WITHIN %s IS NOT SET CORRECTLY!!"), *this->GetName());
		return;
	}

	ACore_GameMode* gameMode = Cast<ACore_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!gameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: CORE GAME MODE NOT CASTED CORRECTLY WITHIN - %s"), *this->GetName());
		return;
	}
	gameMode->LevelCompleteEvent.AddUObject(this, &ACore_HUD::ToggleVictoryScreenWidget);
	gameMode->WaveDefeatedEvent.AddUObject(this, &ACore_HUD::DisplayStartNextWaveModal);

	bPlayerHasLost = false;

	SetUpInGameWidgetList();
	SetUpGameMenusWidgetList();
	SetUpMenusWidgetList();
	SetUpModalWidgetList();

	BindDelegates();

	SetFocusToGame();

	if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == "Level1")
	{
		FTimerHandle DisplayTutorialHudHandle;
		GetWorld()->GetTimerManager().SetTimer(DisplayTutorialHudHandle, this, &ACore_HUD::DisplayTutorialHud, 0.1f, false);
	}

	FTimerHandle DisplayOpenTurretsModelHandle;
	GetWorld()->GetTimerManager().SetTimer(DisplayOpenTurretsModelHandle, this, &ACore_HUD::DisplayOpenTurretMenuModal, 0.5f, false);
}

void ACore_HUD::BindDelegates()
{
	turretSelectionMenu->OnMenuSelectionEvent.AddDynamic(playerHud->WeaponAndTurretSelector, &UHUDWeaponTurretSelector::GetInfoFromTurretMenu);

	APlayerCharacter* player = Cast<APlayerCharacter>(localCorePlayerController->GetPawn());
	if (!player)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindDelegates: PLAYER NOT CASTED CORRECTLY WITHIN - %s"), *this->GetName());
		return;
	}
	player->OnHealthUpdatedEvent.AddUObject(playerHud->HealthAndMana, &UHUDHealthAndMana::UpdateHealthBar);
	player->OnManaUpdatedEvent.AddUObject(playerHud->HealthAndMana, &UHUDHealthAndMana::UpdateManaBar);
	player->OnPlayerDeathStateEvent.AddUObject(this, &ACore_HUD::PlayerDefeatedState);


	AGameStateBase* gameState = UGameplayStatics::GetGameState(GetWorld());
	ACore_GameState* coreGameState = Cast<ACore_GameState>(gameState);
	if (!coreGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindDelegates: CORE GAME STATE NOT CASTED CORRECTLY WITHIN - %s"), *this->GetName());
		return;
	}
	coreGameState->OnPlayerLostEvent.AddUObject(this, &ACore_HUD::PlayerLost);

	localCorePlayerController->PauseGameEvent.BindUObject(this, &ACore_HUD::TogglePauseMenu);
	localCorePlayerController->GetTurretDAEvent.BindUObject(playerHud->WeaponAndTurretSelector, &UHUDWeaponTurretSelector::GetTurretClassFromArray);

	pauseMenu->ContinueButtonPressedEvent.BindUObject(this, &ACore_HUD::TogglePauseMenu);
	pauseMenu->TutorialButtonPressedEvent.BindUObject(this, &ACore_HUD::DisplayTutorialHud);

	if (!tutorialMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindDelegates: HUD TUTORIAL MENU NOT SET CORRECTLY WITHIN - %s"), *this->GetName());
		return;
	}

	tutorialMenu->CloseTutorialEvent.BindUObject(this, &ACore_HUD::DisplayTutorialHud);

}

bool ACore_HUD::CheckVaildWidgetPointer(TSubclassOf<UUserWidget> widgetClass)
{
	if (widgetClass)
	{
		UE_LOG(LogTemp, Display, TEXT("CheckVaildWidgetPointer: Widget Class is valid - %s"), *widgetClass->GetName());
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CheckVaildWidgetPointer: A WIDGET CLASS IS NOT SET WITHIN CORE_HUD!!"));
		return false;
	}
}

void ACore_HUD::SetFocusToGame()
{
	//Set focus to the game
	FInputModeGameOnly inputModeGameOnly;
	localCorePlayerController->SetInputMode(inputModeGameOnly);

	//Hide cursor
	localCorePlayerController->SetShowMouseCursor(false);

	if (gameMenuWidgetToFocus != nullptr)
	{
		gameMenuWidgetToFocus->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void ACore_HUD::SetFocusToWidget()
{
	gameMenuWidgetToFocus->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	FInputModeGameAndUI inputModeGameAndUI;
	localCorePlayerController->SetInputMode(inputModeGameAndUI);
	localCorePlayerController->SetShowMouseCursor(true);

	//Sets Mouse Location to the Centre of the screen.
	FVector2D viewportSize;
	GEngine->GameViewport->GetViewportSize(viewportSize);
	localCorePlayerController->SetMouseLocation((viewportSize.X / 2), (viewportSize.Y / 2));
}

void ACore_HUD::SetUpInGameWidgetList()
{
	bInGameWidgetsEnabled = false;

	if(CheckVaildWidgetPointer(playerHudClass))
	{
		playerHud = CreateWidget<UHUDPlayerHud>(localCorePlayerController, playerHudClass);
		inGameWidgetList.Add(playerHud);
	}

	for (UUserWidget* widget : inGameWidgetList)
	{
		if (widget == nullptr)
		{
			UE_LOG(LogTemp, Fatal, TEXT("SetUpInGameWidgetList: WIDGET IS RETURNING NULL WITHIN CORE HUD, SET UP IN GAME WIDGET LIST FUNCTION"));
			return;
		}
		widget->AddToViewport();
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}

	ToggleInGameWidgets();
}

void ACore_HUD::ToggleInGameWidgets()
{

	if (bInGameWidgetsEnabled)
	{
		for (UUserWidget* widget : inGameWidgetList)
		{
			widget->SetVisibility(ESlateVisibility::Collapsed);
		}
		bInGameWidgetsEnabled = false;
	}
	else
	{
		for (UUserWidget* widget : inGameWidgetList)
		{
			widget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		bInGameWidgetsEnabled = true;
	}
}

void ACore_HUD::SetUpGameMenusWidgetList()
{
	if (CheckVaildWidgetPointer(turretSelectionMenuClass))
	{
		turretSelectionMenu = CreateWidget<UHUDTurretSelectionMenu>(localCorePlayerController, turretSelectionMenuClass);
		turretSelectionMenu->SetUpWidget(turretInfo);
		gameMenusWidgetList.Add(turretSelectionMenu);
	}
	
	if (CheckVaildWidgetPointer(victoryScreenClass))
	{
		victoryScreenMenu = CreateWidget<UHUDVictoryScreen>(localCorePlayerController, victoryScreenClass);
		gameMenusWidgetList.Add(victoryScreenMenu);
	}

	if (CheckVaildWidgetPointer(playerDefeatedClass))
	{
		playerDefeatedMenu = CreateWidget<UHUDPlayerDefeated>(localCorePlayerController, playerDefeatedClass);
		gameMenusWidgetList.Add(playerDefeatedMenu);
	}

	if (CheckVaildWidgetPointer(playerLostClass))
	{
		playerLostMenu = CreateWidget<UHUDPlayerLost>(localCorePlayerController, playerLostClass);
		gameMenusWidgetList.Add(playerLostMenu);
	}

	if (CheckVaildWidgetPointer(pausedClass))
	{
		pauseMenu = CreateWidget<UHUDPauseMenu>(localCorePlayerController, pausedClass);
		gameMenusWidgetList.Add(pauseMenu);
	}

	if (CheckVaildWidgetPointer(tutorialClass))
	{
		tutorialMenu = CreateWidget<UHUDTutorial>(localCorePlayerController, tutorialClass);
		gameMenusWidgetList.Add(tutorialMenu);
	}

	for (UUserWidget* widget : gameMenusWidgetList)
	{
		widget->AddToViewport();
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ACore_HUD::ToggleGameMenuWidgets(UUserWidget* widget)
{
	if (widget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ToggleGameMenuWidgets: WIDGET IS RETURNING NULL WITHIN - %s"), *this->GetName());
		return;
	}

	gameMenuWidgetToFocus = widget;

	for (UUserWidget* widgetInList : gameMenusWidgetList)
	{
		if (widgetInList == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ToggleGameMenuWidgets: widgetInList IS RETURNING NULL WITHIN CORE HUD gameMenusWidgetList array - %s"), *this->GetName());
			return;
		}

		if (widgetInList == gameMenuWidgetToFocus && widgetInList->GetVisibility() == ESlateVisibility::Collapsed)
		{
			SetFocusToWidget();
			widgetInList->SetVisibility(ESlateVisibility::Visible);
		}
		else if (widgetInList->GetVisibility() == ESlateVisibility::Visible)
		{
			SetFocusToGame();
			widgetInList->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

}

void ACore_HUD::SetUpMenusWidgetList()
{
	//menusWidgetList.Add()

	/*for (UUserWidget* widget : menusWidgetList)
	{
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}*/
}

void ACore_HUD::SetUpModalWidgetList()
{
	if (CheckVaildWidgetPointer(openTurretMenuModalClass))
	{
		openTurretModal = CreateWidget<UModalBaseClass>(localCorePlayerController, openTurretMenuModalClass);
		openTurretModal->SetText(FText::FromString(TEXT("Open Turret Menu By Pressing TAB!")));
		modalWidgetList.Add(openTurretModal);
	}

	if (CheckVaildWidgetPointer(startNextWaveModalClass))
	{
		startNextWaveModal = CreateWidget<UModalBaseClass>(localCorePlayerController, startNextWaveModalClass);
		startNextWaveModal->SetText(FText::FromString(TEXT("Start The Next Wave By Pressing ENTER!")));
		modalWidgetList.Add(startNextWaveModal);
	}

	for (UUserWidget* widget : modalWidgetList)
	{
		widget->AddToViewport();
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ACore_HUD::ToggleModalWidgets(UModalBaseClass* modalWidget)
{
	for (UUserWidget* modal : modalWidgetList)
	{
		modal->SetVisibility(ESlateVisibility::Collapsed);
	}
	modalWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	modalWidget->PlayStartAnimation();
}

void ACore_HUD::DisplayStartNextWaveModal()
{
	if (!startNextWaveModal)
	{
		UE_LOG(LogTemp, Error, TEXT("DisplayStartNextWaveModal: startNextWaveModal NOT SET CORRECTLY WITIN - %s"), *this->GetName());
		return;
	}
	ToggleModalWidgets(startNextWaveModal);
}

void ACore_HUD::DisplayOpenTurretMenuModal()
{
	if (!openTurretModal)
	{
		UE_LOG(LogTemp, Error, TEXT("DisplayOpenTurretMenuModal: openTurretModal NOT SET CORRECTLY WITIN - %s"), *this->GetName());
		return;
	}
	ToggleModalWidgets(openTurretModal);
}



void ACore_HUD::ToggleTurretSelectionWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleTurretSelectionWidget: Toggle Turret Selection"));
	ToggleGameMenuWidgets(turretSelectionMenu);

	if (turretSelectionMenu->GetVisibility() == ESlateVisibility::Collapsed)
	{
		DisplayStartNextWaveModal();
	}
}

void ACore_HUD::ToggleVictoryScreenWidget()
{
	//A Check to see if the player has already lost. The last enemy in the level could be defeated by colliding with the defending base, thats why this check is here
	if (bPlayerHasLost)
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("ToggleVictoryScreenWidget: Toggle Victory Screen Widget"));
	ToggleGameMenuWidgets(victoryScreenMenu);
	victoryScreenMenu->PlayVictoryAnimation();
	localCorePlayerController->DisableInput(localCorePlayerController);
}

void ACore_HUD::PlayerDefeatedState(bool bIsPlayerDefeated, float respwanTime)
{

	if (bIsPlayerDefeated)
	{
		ToggleGameMenuWidgets(playerDefeatedMenu);
		playerDefeatedMenu->StartCountdown(respwanTime);
	}
	else
	{
		playerDefeatedMenu->EndCountdown();
		ToggleGameMenuWidgets(playerDefeatedMenu);
	}
}

void ACore_HUD::PlayerLost()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerLost: Player Lost Called"));
	if (bPlayerHasLost == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerLost: Player Lost HUD Called"));
		ToggleGameMenuWidgets(playerLostMenu);
		playerLostMenu->PlayLostAnimation();
		bPlayerHasLost = true;
	}
}

void ACore_HUD::TogglePauseMenu()
{
	UE_LOG(LogTemp, Display, TEXT("TogglePauseMenu: Called from core HUD"));
	ToggleGameMenuWidgets(pauseMenu);

	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

bool ACore_HUD::GetIsTurretSelectionMenuVisable()
{
	return turretSelectionMenu->IsVisible();
}

void ACore_HUD::DisplayTutorialHud()
{
	UE_LOG(LogTemp, Warning, TEXT("DisplayTutorialHud: Display Tutorial Hud was called"));

	ToggleGameMenuWidgets(tutorialMenu);

	if (tutorialMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}
