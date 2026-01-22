#include "DefendingBase.h"
#include "Components/SphereComponent.h"
#include "EnemyCharacterBase.h"

ADefendingBase::ADefendingBase()
{
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = baseMesh;

	enemyCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	enemyCollisionDetection->SetupAttachment(baseMesh);

	enemyCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &ADefendingBase::OnOverlap);

	maxBaseHealth = 5;

}

void ADefendingBase::BeginPlay()
{
	Super::BeginPlay();
	currentBaseHealth = maxBaseHealth;
	bPlayerLost = false;
}

void ADefendingBase::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Defeats the enenmy that overlapped and calls to update the base health count
	if (OtherActor->IsA(AEnemyCharacterBase::StaticClass()))
	{
		currentBaseHealth = FMath::Clamp(currentBaseHealth - 1, 0, maxBaseHealth);
		BaseHealthDecreasedEvent.ExecuteIfBound(currentBaseHealth);
		UE_LOG(LogTemp, Display, TEXT("OnOverlap: Base Health Decreaced to - %d"), currentBaseHealth);
		
		AEnemyCharacterBase* enemy = Cast<AEnemyCharacterBase>(OtherActor);
		enemy->OnDeath();

		//If the base has reached 0, call to end the level.
		if (currentBaseHealth <= 0 && bPlayerLost == false)
		{
			BaseHealthReachedZeroEvent.ExecuteIfBound();
			UE_LOG(LogTemp, Warning, TEXT("OnOverlap: Base Health Has Reached 0!!"));
			bPlayerLost = true;
		}
	}
}

int ADefendingBase::GetBaseHealth()
{
	return currentBaseHealth;
}

