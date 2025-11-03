// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_TurretStats.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UDA_TurretStats : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/**
	* The amount of damage this Turret does to the enemy actors
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	float damageAmount;

	/**
	* The damage type that the Turret deals
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	TSubclassOf<UDamageType> damageType;

	/**
	* The amount of time the Turret is active for when it detects and enemy
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	float activeTime;

	/**
	* The time it takes to recharge the Turret after it has been used
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	float rechargeTime;

	/**
	* The cost to place down the Turret
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	int cost;
};
