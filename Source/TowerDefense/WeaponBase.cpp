#include "WeaponBase.h"
#include "DrawDebugHelpers.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = weaponMesh;

	spawnProjectileComponent = CreateDefaultSubobject<UAC_SpawnProjectile>(TEXT("Spawn Projectile Component"));
}

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