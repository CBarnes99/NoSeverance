// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = weaponMesh;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	damageDelt = weaponStats->damageDelt;
	currentAmmo = weaponStats->ammoMax;
	maxAmmo = weaponStats->ammoMax;

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::spawnProjectile(const FRotator& cameraRotation)
{
	if (!projectile)
		{
			UE_LOG(LogTemp, Error, TEXT("Projectile class is not set on Weapon Base!"));
			return;
		}

	FVector muzzleLocation = weaponMesh->GetSocketLocation(FName("Muzzle"));
	FRotator spawnRotation = cameraRotation;
	FVector shootDirection = cameraRotation.Vector();
	FVector spawnLocation = muzzleLocation + shootDirection * 10.0f;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();

	AProjectileBase* spawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectile, spawnLocation, cameraRotation, spawnParams);
	spawnedProjectile->FireInDirection(shootDirection);
}

