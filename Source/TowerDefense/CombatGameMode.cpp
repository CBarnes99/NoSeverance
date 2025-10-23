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
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<ACombatPlayerController> CombatPlayerControllerClass(TEXT("/Game/BP_CombatPlayerController.BP_CombatPlayerController"));
	PlayerControllerClass = CombatPlayerControllerClass.Class;*/


	currentWave = 0;
}


void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatGameMode::StartEnemyWave()
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
		spawnerManager->SetAllSpawners();
	}
	
	//cCeck to see if the last wave has been initilized
	if (!lastWave)
	{
		lastWave = spawnerManager->CalculateLastWave();
		UE_LOG(LogTemp, Warning, TEXT("The last wave of this level is: %i"), lastWave);		
	}

	//Check to see if a wave is already active
	if (!spawnerManager->IsWaveActive())
	{
		currentWave++;
		spawnerManager->StartSpawningEnemies(currentWave);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave is already active!"));
	}
}
