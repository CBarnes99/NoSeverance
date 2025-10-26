// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PlayerCharacterStats.generated.h"

UCLASS(Blueprintable)
class TOWERDEFENSE_API UDA_PlayerCharacterStats : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FString name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float movementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float runSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float jumpHeight;
	
};
