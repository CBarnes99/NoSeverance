// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_EnemyCharacterStats.generated.h"

UCLASS(Blueprintable)
class TOWERDEFENSE_API UDA_EnemyCharacterStats : public UDataAsset
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FString name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float damageDelt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float movementSpeed;

};
