#include "TurretStatic.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "DA_TurretInfo.h"

ATurretStatic::ATurretStatic()
{
	PrimaryActorTick.bCanEverTick = false;

	invisableRootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Invisable Root Mesh"));
	RootComponent = invisableRootMesh;
	invisableRootMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(RootComponent);

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision Area"));
	collisionBox->SetCollisionProfileName(TEXT("Trigger"));
	collisionBox->SetGenerateOverlapEvents(true);
	collisionBoxSize = FVector(150, 50, 50);
	collisionBox->SetBoxExtent(FVector(collisionBoxSize));
	collisionBox->SetRelativeLocation(FVector(collisionBoxSize.X, 0, 0));
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATurretStatic::OnOverlap);

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Texture"));
	collisionMesh->SetCollisionProfileName("NoCollision", false);

    collisionBox->SetupAttachment(RootComponent);
	collisionMesh->SetupAttachment(collisionBox);
}

void ATurretStatic::OnConstruction(const FTransform& Transform)
{
	//This sets the visual of the damage zone to the same size as the collision box
	collisionMesh->SetRelativeScale3D(collisionBoxSize / 125);
}

void ATurretStatic::BeginPlay()
{
	Super::BeginPlay();

	turretActive = true;
}

void ATurretStatic::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(AEnemyCharacterBase::StaticClass()) && !damagedActors.Contains(OtherActor) && turretActive)
    {
		AEnemyCharacterBase* enemy = Cast<AEnemyCharacterBase>(OtherActor);
		if (enemy->GetIsEnemyDisabled())
		{
			return;
		}

		if (GetLocalRole() == ROLE_Authority)
		{
			UE_LOG(LogTemp, Display, TEXT("OnOverlap: %s Overlaps %s"), *OtherActor->GetName(), *this->GetName());

			UGameplayStatics::ApplyDamage(OtherActor, turretStats->damageAmount, GetInstigatorController(), this, UDamageType::StaticClass());
			damagedActors.Add(OtherActor);

			//A Timer for How long the turret is active for when it is triggered, when the timer goes off, it disables the turret
			if (!GetWorld()->GetTimerManager().IsTimerActive(activeAndRechargeTimerHandle))
			{
				GetWorld()->GetTimerManager().SetTimer(activeAndRechargeTimerHandle, this, &ATurretStatic::DisableTurret, turretStats->activeTime, false);
			}
		}
    }
}

void ATurretStatic::DisableTurret()
{
	UE_LOG(LogTemp, Display, TEXT("DisableTurret: %s is disabled"), *this->GetName());
	collisionBox->SetGenerateOverlapEvents(false);
	turretActive = false;
	damagedActors.Empty();
	GetWorld()->GetTimerManager().SetTimer(activeAndRechargeTimerHandle, this, &ATurretStatic::EnableTurret, turretStats->rechargeTime, false);
}

void ATurretStatic::EnableTurret()
{
	UE_LOG(LogTemp, Display, TEXT("EnableTurret: %s is enabled"), *this->GetName());
	if (GetWorld()->GetTimerManager().IsTimerActive(activeAndRechargeTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(activeAndRechargeTimerHandle);
	}

	turretActive = true;
	collisionBox->SetGenerateOverlapEvents(true);
}
