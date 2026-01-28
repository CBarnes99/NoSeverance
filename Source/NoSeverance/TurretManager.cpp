#include "TurretManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "AC_PlaceActor.h"
#include "Core_GameState.h"
#include "DA_TurretInfo.h"
#include "SpawnerManager.h"
#include "Core_GameMode.h"
#include "TurretStatic.h"

ATurretManager::ATurretManager()
{
	PrimaryActorTick.bCanEverTick = false;

	placeActorComponent = CreateDefaultSubobject<UAC_PlaceActor>(TEXT("Place Actor Component"));
}

void ATurretManager::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
	
}

void ATurretManager::BindDelegates()
{
	placeActorComponent->PlacedActorEvent.BindUObject(this, &ATurretManager::AddTurretToArray);

	AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld());
	ACore_GameMode* coreGameMode = Cast<ACore_GameMode>(gameMode);
	if (!coreGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("BindDelegates: CORE GAME MODE NOT CASTED CORRECTLY WITHIN - %s"), *this->GetName());
		return;

	}
	coreGameMode->WaveDefeatedEvent.AddUObject(this, &ATurretManager::EnableAllTurrets);


	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnerManager::StaticClass());
	ASpawnerManager* spawnerManager = Cast<ASpawnerManager>(actor);
	if (!spawnerManager)
	{
		UE_LOG(LogTemp, Error, TEXT("BindDelegates: SPAWNER MANAGER NOT CASTED CORRECTLY WITHIN - %s"), *this->GetName());
		return;
	}
	spawnerManager->EnemyDropsHaveFinishedPoolingEvent.BindUObject(this, &ATurretManager::AddActorsToIgnoreList);
}

void ATurretManager::StartTurretPlacement(UDA_TurretInfo* turretInfo)
{
	if (!turretInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("StartTurretPlacement: Turret Info Within Turret Manager - Start Turret Placement Is NULL!!!"));
		return;
	}
	currentTurretInfo = turretInfo;

	placeActorComponent->StartPlacement(TSubclassOf<AActor>(*currentTurretInfo->turretClass));
}

void ATurretManager::ConfirmTurretPlacement()
{

	if (IsAbleToPlaceTurret())
	{
		coreGameState->UpdatePlayerCurrencyAmount(false, currentTurretInfo->cost);
		UE_LOG(LogTemp, Warning, TEXT("ConfirmTurretPlacement: Spawned Turret! - New Player Currency = %f, Turret Cost = %d"), coreGameState->GetPlayerCurrencyAmount(), currentTurretInfo->cost);
		placeActorComponent->ConfirmPlacement();
	}
	else
	{
		//create notifcation to let the player know they cant place the turret
		UE_LOG(LogTemp, Warning, TEXT("ConfirmTurretPlacement: Cant Spawn Turret! - Player Currency = %f, Turret Cost = %d"), coreGameState->GetPlayerCurrencyAmount(), currentTurretInfo->cost);
	}
}

bool ATurretManager::IsAbleToPlaceTurret()
{
	if (!coreGameState)
	{
		AGameStateBase* gameState = UGameplayStatics::GetGameState(GetWorld());
		coreGameState = Cast<ACore_GameState>(gameState);
		if (!coreGameState)
		{
			UE_LOG(LogTemp, Error, TEXT("ConfirmTurretPlacement: CORE GAME STATE NOT SET CORRECTLY IN - %s"), *this->GetName());
			return false;
		}
	}

	if (currentTurretInfo->cost <= coreGameState->GetPlayerCurrencyAmount())
		return true;

	return false;
}

void ATurretManager::CancelTurretPlacement()
{
	placeActorComponent->CancelPlacement();
}

void ATurretManager::RotateTurretPlacement(float directon)
{
	placeActorComponent->RotatePlacement(directon);
}

bool ATurretManager::IsPlacingTurret()
{
	return placeActorComponent->IsPlacing();
}

void ATurretManager::UpdateIgnoreActors(AActor* actor, bool addToArray)
{
	placeActorComponent->UpdateIgnoreActors(actor, addToArray);
}

void ATurretManager::UpdateTurretPlacementLocation(FVector traceStartLocation, FVector forwardVector)
{
	placeActorComponent->UpdatePlacementLocation(traceStartLocation, forwardVector);
}

void ATurretManager::AddTurretToArray(AActor* actor)
{
	ATurretStatic* turret = Cast<ATurretStatic>(actor);
	if (!turret)
	{
		UE_LOG(LogTemp, Error, TEXT("AddTurretToArray: actor is not an ATurretStatic, it is a - %s"), *actor->GetName());
		return;
	}
	placedTurretsArray.Add(turret);
}

void ATurretManager::AddActorsToIgnoreList(TArray<AActor*> enemyDropArray)
{
	for (AActor* actor : enemyDropArray)
	{
		placeActorComponent->UpdateIgnoreActors(actor, true);
	}
}

void ATurretManager::EnableAllTurrets()
{
	for (ATurretStatic* turret : placedTurretsArray)
	{
		turret->EnableTurret();
	}
}
