#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_TurretStats.generated.h"

UCLASS(Blueprintable)
class TOWERDEFENSE_API UDA_TurretStats : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/**
	* @brief The amount of damage this Turret does to the enemy actors
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	float damageAmount;

	/**
	* @brief The damage type that the Turret deals
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	TSubclassOf<UDamageType> damageType;

	/**
	* @brief The amount of time the Turret is active for when it detects and enemy
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	float activeTime;

	/**
	* @brief The time it takes to recharge the Turret after it has been used
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	float rechargeTime;

	/**
	* @brief The cost to place down the Turret
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	int cost;
};
