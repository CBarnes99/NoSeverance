// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = weaponMesh;

	spawnProjectileComponent = CreateDefaultSubobject<UAC_SpawnProjectile>(TEXT("Spawn Projectile Component"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	damageDelt = weaponStats->damageDelt;
	currentAmmo = weaponStats->ammoMax;
	maxAmmo = weaponStats->ammoMax;
	projectileSpeed = weaponStats->projectileSpeed;
	weaponMuzzleName = weaponStats->muzzleName;

	//UE_LOG(LogTemp, Warning, TEXT("In Weapon Base!! Owner = %s, Instigator - %s"), *GetOwner()->GetName(), *GetInstigator()->GetName());
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AWeaponBase::GetWeaponMuzzleLocation()
{
	return weaponMesh->GetSocketLocation(weaponMuzzleName);
}

float AWeaponBase::GetDamageDelt()
{
	return damageDelt;
}

float AWeaponBase::GetProjectileSpeed()
{
	return projectileSpeed;
}