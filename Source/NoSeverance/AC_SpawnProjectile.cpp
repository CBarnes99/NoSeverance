#include "AC_SpawnProjectile.h"
#include "DrawDebugHelpers.h"
#include "ProjectileBase.h"

UAC_SpawnProjectile::UAC_SpawnProjectile()
{
	PrimaryComponentTick.bCanEverTick = false;

	poolSize = 5;
}

void UAC_SpawnProjectile::BeginPlay()
{
	Super::BeginPlay();
	amountInPool = 0;

	//InitializePool();
}

void UAC_SpawnProjectile::InitializePool(float fireRate, float lifetime)
{
	if (!projectile)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializePool: No Projectile Class Within - %s"), *this->GetOwner()->GetName());
		return;
	}

	poolSize = fireRate * lifetime;
	//UE_LOG(LogTemp, Display, TEXT("InitializePool: poolsize = %f"), poolsize);

	for (int i = 0; i < poolSize; i++)
	{
		SpawnProjectile();
	}
	UE_LOG(LogTemp, Warning, TEXT("InitializePool: There are %d projectiles pooled"), amountInPool);


	TArray<AActor*> projectilesToIgnore;
	for (AProjectileBase* projectileFromPool : projectilePool)
	{
		projectilesToIgnore.Add(Cast<AActor>(projectileFromPool));
	}
	targetLocaionQueryParams.AddIgnoredActors(projectilesToIgnore);
}

void UAC_SpawnProjectile::SpawnProjectile()
{
	TRACE_BOOKMARK(TEXT("SpawnProjectile: SpawnedProjectile"));
	amountInPool++;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetOwner()->GetInstigator();
	AProjectileBase* pooledProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectile, FVector::ZeroVector, FRotator::ZeroRotator, spawnParams);

	FString lable = FString::Printf(TEXT("%s - %d"), *projectile->GetName(), amountInPool);
	projectilePool.Add(pooledProjectile);

}

void UAC_SpawnProjectile::FireProjectile(FVector traceStartLocation, FVector weaponMuzzleLocation, FVector actorForwardVector, float damageDelt, float projectileSpeed, float projectileLifetime, UNiagaraSystem* particalEffect)
{
	TRACE_BOOKMARK(TEXT("FiredProjectile"));
	if (!projectile)
	{
		UE_LOG(LogTemp, Error, TEXT("FireProjectile: Projectile class is not set in AC_SpawnProjectile within %s!"), *GetOwner()->GetName());
		return;
	}

	FVector targetLocation = GetTraceTargetLocation(traceStartLocation, actorForwardVector);

	FVector shootDirection = (targetLocation - weaponMuzzleLocation).GetSafeNormal();

	FRotator spawnRotation = shootDirection.Rotation();

	FVector spawnLocation = weaponMuzzleLocation + shootDirection * 10.0f;


	//FOR DEBUGGING, SPAWNS IN THE PROJECTILE INSTEAD OF FROM THE POOL
	/*FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetOwner()->GetInstigator();
	AProjectileBase* currentProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectile, spawnLocation, spawnRotation, spawnParams);*/

	AProjectileBase* currentProjectile = GetInactiveProjectile();

	if (!currentProjectile)
	{
		SpawnProjectile();
		currentProjectile = GetInactiveProjectile();
		poolSize++;
		UE_LOG(LogTemp, Error, TEXT("FireProjectile: Added another projectile to the pool for - %s. There are %f projectiles within the pool"), *GetOwner()->GetName(), poolSize);
	}

	//UE_LOG(LogTemp, Warning, TEXT("FireProjectile: Using - %s"), *currentProjectile->GetName());
	currentProjectile->SetActorLocation(spawnLocation);
	currentProjectile->SetActorRotation(spawnRotation);

	if (!currentProjectile->GetDefualtsBeenSet())
	{
		currentProjectile->SetProjectileDefaults(damageDelt, projectileSpeed, projectileLifetime, particalEffect);
	}
	currentProjectile->FireInDirection(shootDirection);
	currentProjectile->ActivateProjectile();

	DrawDebugSphere(GetWorld(), targetLocation, 15.f, 12, FColor::Green, false, 2.f);
	//UE_LOG(LogTemp, Display, TEXT("FireProjectile: Velocity = %s"), *currentProjectile->projectileMovementComponent->Velocity.ToString());

}

AProjectileBase* UAC_SpawnProjectile::GetInactiveProjectile()
{
	for (AProjectileBase* p : projectilePool)
	{
		if (!p->IsProjectileActive()) return p;
	}
	//UE_LOG(LogTemp, Error, TEXT("GetInactiveProjectile: No Inactive Projectiles Within %s. Create A Larger Pool Size"), *this->GetOwner()->GetName());
	return nullptr;
}

FVector UAC_SpawnProjectile::GetTraceTargetLocation(FVector traceStartLocation, FVector actorForwardVector)
{
	FVector targetPos = FVector::ZeroVector;
	FHitResult hit;
	FVector traceEnd = traceStartLocation + actorForwardVector * 5000.f;

	GetWorld()->LineTraceSingleByChannel(hit, traceStartLocation, traceEnd, ECC_Pawn, targetLocaionQueryParams);

	DrawDebugLine(GetWorld(), traceStartLocation, traceEnd, FColor::Red, false, 2.f, 1.f);

	targetPos = hit.bBlockingHit ? hit.ImpactPoint : traceEnd;

	return targetPos;
}
