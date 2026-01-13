#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_EnemyDrop.h"
#include "EnemyDrop.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyDrop : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyDrop();

	/** Enables the drop if there is a disabled drop in the pool, called from Spawner Manager */
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	void EnableDrop(EEnemyDrop enemyDropType, FVector enemyDropLocation);

	/** When drop is picked up by the player, the drop is disabled and returned to the pool in the Spawner Manager */
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	void DisableDrop();

	/** A check called from the Spawner Manager to check if this drop is currently disabled or not */
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	bool IsDropDisabled();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* dropMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class USphereComponent* collisionComponent;

	/** The Drop type is set when SetDrop is called, and is used for OnPickUp to do a task depending on the value of dropType */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	EEnemyDrop dropType;

	/** Sets the type of drop the enemy drops
	* @param type The type of pickup you want the enemy to drop, as an EEnemyDrop */
	UFUNCTION(BlueprintCallable)
	void SetDrop(EEnemyDrop type);

	/** Built in overlap function */
	UFUNCTION(BlueprintCallable)
	void OnPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "DropValue")
	TMap<EEnemyDrop, TSoftObjectPtr<UStaticMesh>> meshMap;

	///** Health potion mesh reference */
	//UPROPERTY(EditAnywhere, Category = "DropMesh")
	//TSoftObjectPtr<UStaticMesh> healthPotionMesh;

	///** Mana potion mesh reference */
	//UPROPERTY(EditAnywhere, Category = "DropMesh")
	//TSoftObjectPtr<UStaticMesh> manaPotionMesh;

	///** Currency mesh reference */
	//UPROPERTY(EditAnywhere, Category = "DropMesh")
	//TSoftObjectPtr<UStaticMesh> currencyMesh;

	/** The amount of health the player is healed for when picked up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropValue")
	float healthPotionHealAmount;

	/** The amount of mana the player gains when picked up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropValue")
	float manaPotionGainAmount;

	/** The amount of currency the player gets when picked up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropValue")
	int smallCurrencyGainAmount;

	/** The amount of currency the player gets when picked up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropValue")
	int largeCurrencyGainAmount;

	FTimerHandle MovementTimerHandle;

	//Bobbing properties
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Motion")
	float rotationSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Motion")
	float bobbingAmplitude;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Motion")
	float bobbingFrequency;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Motion")
	float timerInterval;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Motion")
	float runningTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Motion")
	FVector initialLocation;

	UFUNCTION(BlueprintCallable, Category = "Motion")
	void UpdateMotion();	
	
	/** A check to see if this drop is disabled */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pooling")
	bool bIsDisabled;
};
