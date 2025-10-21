// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"
#include <Kismet/GameplayStatics.h>
#include "EnemySpawner.h"


// Sets default values
ASpawnerManager::ASpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	waveActive = false;
	amountOfEnemysInRound = 0;
}

// Called when the game starts or when spawned
void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASpawnerManager::isWaveActive()
{
	return waveActive;
}

void ASpawnerManager::startSpawningEnemies(int currentWave)
{
	//if the spawners haven't been set, set the spawners
	if (!enemySpawners.IsValidIndex(0))
	{
		setAllSpawners();
	}
	
	//If there isnt a wave currently active, start the wave
	if (!waveActive)
	{
		waveActive = true;

		UE_LOG(LogTemp, Warning, TEXT("current wave = %d"), currentWave);

		//Gets the amount of enemies that are in this round and starts spawning
		for (AActor* Actor : enemySpawners)
		{
			AEnemySpawner* spawner = Cast<AEnemySpawner>(Actor);
			if (spawner)
			{
				spawner->currentWaveBeingSpawned = currentWave;
				amountOfEnemysInRound += spawner->amountOfEnemiesInWave();
				spawner->StartSpawning();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Spawner Found when spawning calulcating amount of enemies"));
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("There are %d enemies this round"), amountOfEnemysInRound);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave is currently active!"));
	}
};

void ASpawnerManager::setAllSpawners()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), enemySpawners);

	UE_LOG(LogTemp, Warning, TEXT("Found %d actors from class AEnemySpawner"), enemySpawners.Num());
}

int ASpawnerManager::calculateLastWave()
{
	int maxWave = 0;
	for (AActor* actor : enemySpawners)
	{
		AEnemySpawner* spawner = Cast<AEnemySpawner>(actor);

		for (auto element : spawner->waveAndEnemyQueue)
		{
			UE_LOG(LogTemp, Warning, TEXT("Key/Wave is %d"), element.Key);
			if (element.Key > maxWave)
			{
				maxWave = element.Key;
				UE_LOG(LogTemp, Warning, TEXT("Max Wave = % d"), maxWave);
			}
		}
	}
	return maxWave;
}
