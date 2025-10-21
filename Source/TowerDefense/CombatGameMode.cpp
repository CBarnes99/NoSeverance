// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "CombatPlayerController.h"
#include <Kismet/GameplayStatics.h>


ACombatGameMode::ACombatGameMode()
{
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_PlayerCharacter"));
	if (PlayerPawnClassFinder.Class)
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find player character Blueprint at /Game/Player/BP_PlayerCharacter"));
	}

	static ConstructorHelpers::FClassFinder<ACombatPlayerController> CombatPlayerControllerClass(TEXT("/Script/Engine.Blueprint/Game/BP_CombatPlayerController"));
	if (CombatPlayerControllerClass.Class)
	{
		PlayerControllerClass = CombatPlayerControllerClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find player controller Blueprint at /Game/BP_CombatPlayerController"));
	}*/

	currentWave = 0;
}


void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatGameMode::startEnemyWave()
{
	//Check to see if there is a valid spawner manager
	if (!spawnerManager)
	{
		AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnerManager::StaticClass());
		spawnerManager = Cast<ASpawnerManager>(actor);
	}

	//Check to see if the spawner manager has all the spawners refereneced
	if (!spawnerManager->enemySpawners.IsValidIndex(0))
	{
		spawnerManager->setAllSpawners();
	}

	if (!lastWave)
	{
		lastWave = spawnerManager->calculateLastWave();
		UE_LOG(LogTemp, Warning, TEXT("The last wave of this level is: %d"), lastWave);
	}

	if (!spawnerManager->isWaveActive())
	{
		currentWave++;
		spawnerManager->startSpawningEnemies(currentWave);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave is already active!"));
	}
}
