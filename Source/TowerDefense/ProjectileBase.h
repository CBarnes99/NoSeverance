#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EnemyCharacterBase.h"
#include "ProjectileBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* @brief The direction you want the projectile to fire
	* @param shootDir The direction you want the projectile to move, as FVector&
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void FireInDirection(const FVector& shootDir);

	/**
	* @brief The amount of damage you want this projectile to deal
	* @param damageAmount The amount of Damage, as a float
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetDamage(float damageAmount);

	/**
	* @brief How fast you want the projectile to fly
	* @param speed The speed of the projectile, as a Float
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetProjectileSpeed(float speed);

	/**
	* @brief A check to see if the projectile is active or in the pool
	* @return True, the projectile is active, False, the projectile is avaliable to use from the pool
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	bool IsProjectileActive();

	/**
	* @brief When the projectile is called to be used, activate it
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void ActivateProjectile();

	/**
	* @brief When the projectile impacts an actor or after the lifetime timer is called, deactivate the projectile
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void DeactivateProjectile();

	/**
	* @brief The projectile movement component
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UProjectileMovementComponent* projectileMovementComponent;

	/**
	* @brief A bool to check if the default damage and speed has been set, to avoid needing to set it each time it is called to be fired
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool hasDefaultsBeenSet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	* @brief The mesh of the projectile
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* projectileMesh;

	/**
	* @brief The collision for the projectile
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* collisionComponent;

	/**
	* @brief The timer handle for the lifetime of the projectile
	*/
	FTimerHandle lifeTimeTimerHandle;

	/**
	* @brief How long you want the projectile to live if it didnt collide with an actor, as a float
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float lifeTime;

	/**
	* @brief A bool to check if the projectile is in use or in the pool
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isActive;

	/**
	* @brief The amount of damage you want the projectile to deal
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float damageDelt;

	/**
	* @brief Default OnHit function
	*/
	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
