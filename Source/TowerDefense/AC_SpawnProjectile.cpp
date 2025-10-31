// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_SpawnProjectile.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UAC_SpawnProjectile::UAC_SpawnProjectile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_SpawnProjectile::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAC_SpawnProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_SpawnProjectile::SpawnProjectile(FVector traceStartLocation, FVector weaponMuzzleLocation, FVector actorForwardVector, float damageDelt, float projectileSpeed)
{
	if (!projectile)
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile class is not set in AC_SpawnProjectile within %s!"), *GetOwner()->GetName());
		return;
	}

	FVector targetLocation = GetTraceTargetLocation(traceStartLocation, actorForwardVector);

	FVector shootDirection = (targetLocation - weaponMuzzleLocation).GetSafeNormal();

	FRotator spawnRotation = shootDirection.Rotation();

	FVector spawnLocation = weaponMuzzleLocation + shootDirection * 10.0f;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetOwner()->GetInstigator();

	AProjectileBase* spawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectile, spawnLocation, spawnRotation, spawnParams);
	spawnedProjectile->SetDamage(damageDelt);
	spawnedProjectile->SetProjectileSpeed(projectileSpeed);
	spawnedProjectile->FireInDirection(shootDirection);
}

FVector UAC_SpawnProjectile::GetTraceTargetLocation(FVector traceStartLocation, FVector actorForwardVector)
{
	FVector targetPos = FVector::ZeroVector;
	FHitResult hit;
	FVector traceEnd = traceStartLocation + actorForwardVector * 100000.f;

	GetWorld()->LineTraceSingleByChannel(hit, traceStartLocation, traceEnd, ECC_Pawn);

	DrawDebugLine(GetWorld(), traceStartLocation, traceEnd, FColor::Red, false, 2.f, 1.f);

	targetPos = hit.bBlockingHit ? hit.ImpactPoint : traceEnd;

	return targetPos;
}