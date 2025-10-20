// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"
#include <Kismet/GameplayStatics.h>
#include "EnemySpawner.h"


// Sets default values
ASpawnerManager::ASpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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


void ASpawnerManager::startSpawningEnemies()
{
	//if the spawners haven't been set, set the spawners
	if (!enemySpawners.IsValidIndex(0))
	{
		setAllSpawners();
	}

	for (AActor* Actor : enemySpawners)
	{
		AEnemySpawner* spawner = Cast<AEnemySpawner>(Actor);
		if (spawner)
		{
			spawner->StartSpawning();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Spawner Found when spawning enemies"));
		}
	}
}

void ASpawnerManager::setAllSpawners()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), enemySpawners);

	UE_LOG(LogTemp, Warning, TEXT("Found %d actors from class AEnemySpawner"), enemySpawners.Num());
}


