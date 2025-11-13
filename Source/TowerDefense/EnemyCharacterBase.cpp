#include "EnemyCharacterBase.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	healthComponent = CreateDefaultSubobject<UAC_Health>(TEXT("Health Componenet"));
}

// Called when the game starts or when spawned
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	name = enemyInfo->name;
	healthComponent->SetHealth(enemyInfo->health);
	movementSpeed = enemyInfo->movementSpeed;
	damageDelt = enemyInfo->damageDelt;

	GetCharacterMovement()->MaxWalkSpeed = movementSpeed;
}

UBehaviorTree* AEnemyCharacterBase::GetBehaviourTree() const
{
	return enemyBehaviorTree;
}
// Called to bind functionality to input
void AEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnemyCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	healthComponent->RecieveDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (healthComponent->GetHealth() <= 0)
	{
		OnDeath();
	}
	return DamageAmount;
}

void AEnemyCharacterBase::OnDeath()
{
	OnEnemyDeathEvent.Broadcast(this);

	Destroy();
	/*
	UE_LOG(LogTemp, Warning, TEXT("Damage Amount = %f"), DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("EventInstigator = %s"), *EventInstigator->GetName())
	UE_LOG(LogTemp, Warning, TEXT("DamageCauser = %s"), *DamageCauser->GetName());
	*/
}
