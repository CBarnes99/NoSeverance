// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileBase.h"
#include "DA_WeaponStats.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UDA_WeaponStats : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float damageDelt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	int ammoMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	AProjectileBase* projectile;
};
