#include "ProjectileBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	collisionComponent->InitSphereRadius(20.f);
	collisionComponent->SetSimulatePhysics(false);
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	collisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	collisionComponent->SetEnableGravity(false);

	RootComponent = collisionComponent;
	collisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	projectileMovementComponent->SetUpdatedComponent(collisionComponent);
	projectileMovementComponent->bRotationFollowsVelocity = true;
	projectileMovementComponent->ProjectileGravityScale = 0.f;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileMesh->SetupAttachment(RootComponent.Get());
	projectileMesh->SetSimulatePhysics(false);

	isActive = false;

	lifeTime = 5.f;

}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();	

	DeactivateProjectile();
}

//These two fucntions are called when the weapon class spawns the projectile and sets the damage and speed values from the weapon data asset
void AProjectileBase::SetDamage(float damageAmount)
{
	damageDelt = damageAmount;
	//UE_LOG(LogTemp, Warning, TEXT("Damage Amount = %f"), damageDelt);
}

void AProjectileBase::SetProjectileSpeed(float speed)
{
	projectileMovementComponent->InitialSpeed = speed;
	projectileMovementComponent->MaxSpeed = speed;
}

bool AProjectileBase::IsProjectileActive()
{
	return isActive;
}

void AProjectileBase::ActivateProjectile()
{
	isActive = true;
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	collisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	GetWorld()->GetTimerManager().SetTimer(lifeTimeTimerHandle, this, &AProjectileBase::DeactivateProjectile, lifeTime, false);

	//UE_LOG(LogTemp, Display, TEXT("Using - %s"), *this->GetName());
}

void AProjectileBase::DeactivateProjectile()
{
	SetProjectileSpeed(0.f);
	projectileMovementComponent->StopMovementImmediately();
	isActive = false;
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	if (GetWorld()->GetTimerManager().IsTimerActive(lifeTimeTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(lifeTimeTimerHandle);
	}
}

void AProjectileBase::FireInDirection(const FVector& shootDir)
{
	projectileMovementComponent->Velocity = shootDir * projectileMovementComponent->InitialSpeed;
}

void AProjectileBase::OnHit(UPrimitiveComponent* hitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//To prevent the projectile from destorying itself when its spawned from the instigator
	if (!OtherActor || OtherActor == this || OtherActor == this->GetInstigator())
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("OtherActor that projectile is colliding with is %s"), *OtherActor->GetName())
	UGameplayStatics::ApplyDamage(OtherActor, damageDelt, GetInstigator()->GetController(), this, NULL /*CHANGE THIS TO A DAMAGE TYPE LATER ON*/);

	DeactivateProjectile();
}