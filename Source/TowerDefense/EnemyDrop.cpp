#include "EnemyDrop.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Core_GameState.h"
#include "DA_EnemyDropInfo.h"

AEnemyDrop::AEnemyDrop()
{
	PrimaryActorTick.bCanEverTick = false;

	dropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drop Mesh"));
	dropMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));

	collisionComponent->InitSphereRadius(20.f);
	collisionComponent->SetSimulatePhysics(false);
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	collisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	collisionComponent->SetEnableGravity(false);

	RootComponent = collisionComponent;
	dropMesh->SetupAttachment(RootComponent);

	collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyDrop::OnPickUp);

	/*healthPotionHealAmount = 20;
	manaPotionGainAmount = 20;
	smallCurrencyGainAmount = 30;
	largeCurrencyGainAmount = 100;*/

}

void AEnemyDrop::BeginPlay()
{
	Super::BeginPlay();

	rotationSpeed = 20.f;
	bobbingAmplitude = 3.f;
	bobbingFrequency = 0.3f;
	timerInterval = 0.02f;
	runningTime = 0.f;

	DisableDrop();
}

void AEnemyDrop::SetDrop(EEnemyDrop type)
{
	dropType = type;

	if (!meshMap.Contains(type))
	{
		UE_LOG(LogTemp, Error, TEXT("SetDrop: EENEMYDROP TYPE MESH NOT SET IN THE MESH MAP WITHIN - %s"), *this->GetName());
		return;
	}

	TSoftObjectPtr<UStaticMesh> meshPtr = meshMap[type];
	if (meshPtr.IsPending())
	{
		meshPtr.LoadSynchronous();
	}
	
	UStaticMesh* loadedMesh = meshPtr.Get();
	
	if (loadedMesh && dropMesh)
	{
		dropMesh->SetStaticMesh(loadedMesh);
	}

	//Temp until I find a mesh that is the correct size
	if (type == EEnemyDrop::SMALL_CURRENCY)
	{
		dropMesh->SetRelativeScale3D(FVector(0.5));
	}
	else
	{
		dropMesh->SetRelativeScale3D(FVector(1));
	}
}

void AEnemyDrop::OnPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnPickUp: %s - Collision Dectected with %s"), *this->GetName(), *OtherActor->GetName());

	if (!OtherActor->IsA(APlayerCharacter::StaticClass())) return;

	if (!enemyDropInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("OnPickUp: ENEMY DROP VALUE IS NOT SET WITHIN - %s"), *this->GetName());
		return;
	}

	float dropValue = enemyDropInfo->dropValues[dropType];

	if (dropValue == NULL || dropValue <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("OnPickUp: Drop Value - %f"), dropValue);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("OnPickUp: Drop Value - %f"), dropValue);
	}

	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	ACore_GameState* gameState = Cast<ACore_GameState>(GetWorld()->GetGameState());

	switch (dropType)
	{
	case EEnemyDrop::HEALTH:
		player->ReceiveHealing(dropValue);
		break;

	case EEnemyDrop::MANA:
		player->ReceiveMana(dropValue);
		break;

	case EEnemyDrop::SMALL_CURRENCY:
		gameState->UpdatePlayerCurrencyAmount(true, dropValue);
		break;

	case EEnemyDrop::LARGE_CURRENCY:
		gameState->UpdatePlayerCurrencyAmount(true, dropValue);
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("OnPickUp: Defualt Switch Statement, create new case in set drop function within EnemyDrop.cpp!!"));
		break;
	}

	DisableDrop();
}

void AEnemyDrop::UpdateMotion()
{
	runningTime += timerInterval;

	float deltaRotation = rotationSpeed * timerInterval;
	FRotator newRotation = GetActorRotation();
	newRotation.Yaw += deltaRotation;

	float bobbingOffset = FMath::Sin(runningTime * 2.f * PI * bobbingFrequency) * bobbingAmplitude;
	FVector newLocation = initialLocation;
	newLocation.Z += bobbingOffset;

	SetActorLocationAndRotation(newLocation, newRotation);
}
void AEnemyDrop::EnableDrop(EEnemyDrop enemyDropType, FVector enemyDropLocation)
{
	SetActorLocation(enemyDropLocation);
	SetDrop(enemyDropType);

	initialLocation = enemyDropLocation;
	GetWorldTimerManager().SetTimer(MovementTimerHandle, this, &AEnemyDrop::UpdateMotion, timerInterval, true);

	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);

	bIsDisabled = false;
}

void AEnemyDrop::DisableDrop()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	if (GetWorldTimerManager().IsTimerActive(MovementTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(MovementTimerHandle);
	}

	bIsDisabled = true;
}
bool AEnemyDrop::IsDropDisabled()
{
	return bIsDisabled;
}
;