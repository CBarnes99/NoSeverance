// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileBase.h"
#include "AC_SpawnProjectile.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAC_SpawnProjectile : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_SpawnProjectile();

	/**
	* @brief Spawns a projectile, and sends it towards a target location
	* @param traceStartLocation A FVector of the starting position where you want to trace a line from, usually the player camera position
	* @param weaponMuzzleLocation A FVector of the location you want the projectile to spawn from. Use mesh->GetSocketLocation(FName Socket Name)
	* @param actorForwardVector A FVector of the forward vector of the actor you want this to spawn from
	* @param damageDelt A Float of the amount of damage you want the projectile to deal
	* @param projectileSpeed A Float of the speed you want the projectile to travel.
	*/
	UFUNCTION(BlueprintCallable)
	void FireProjectile(FVector traceStartLocation, FVector weaponMuzzleLocation, FVector actorForwardVector, float damageDelt, float projectileSpeed);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	class TSubclassOf<AProjectileBase> projectile;

	UFUNCTION(BlueprintCallable)
	AProjectileBase* GetInactiveProjectile();

	UFUNCTION(BlueprintCallable)
	FVector GetTraceTargetLocation(FVector traceStartLocation, FVector actorForwardVector);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<AProjectileBase*> traceIgnoreActors;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TArray<AProjectileBase*> projectilePool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	int poolSize;
};


