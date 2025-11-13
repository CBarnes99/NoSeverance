#pragma once

#include "EnemyAIController.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "DA_EnemyCharacterStats.h"
#include "AC_Health.h"
#include "EnemyCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeathSignature, AEnemyCharacterBase*, Enemy);

UCLASS()
class TOWERDEFENSE_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacterBase();

	UFUNCTION(BlueprintCallable)
	UBehaviorTree* GetBehaviourTree() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEnemyDeathSignature OnEnemyDeathEvent;

protected:
	virtual void BeginPlay() override;

	/**
	* @brief A pointer to the the Behaviour Tree assigned in the editor
	*/
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* enemyBehaviorTree;

	/**
	* @brief The health component so the enemies can reduce in health when damaged
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	class UAC_Health* healthComponent;

	/**
	* @brief Assign a Data Asset in Blueprints for each of the enemys information
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	TObjectPtr<UDA_EnemyCharacterStats> enemyInfo;

	/**
	* @brief The name of the enemy assined from the data asset, as FString
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	FString name;

	/**
	* @brief The damage delt from the enemy assined from the data asset, as a float
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float damageDelt;

	/**
	* @brief The speed of the enemy assined from the data asset, as a float
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float movementSpeed;

	//The built in take damage function
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/**
	* @brief When the enemy loses all their health, on death is called
	*/
	UFUNCTION(BlueprintCallable)
	void OnDeath();
};
