#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PlayerCharacterStats.generated.h"

UCLASS(Blueprintable)
class TOWERDEFENSE_API UDA_PlayerCharacterStats : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/**
	* @brief The name of your player character
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FString name;

	/**
	* @brief The health of your player character
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float health;

	/**
	* @brief The amount of mana your player character has
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float mana;

	/**
	* @brief How fast you want the base movement speed of your player character to be
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float movementSpeed;

	/**
	* @brief How fast you want the player character to move when running
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float runSpeed;

	/**
	* @brief How high you want the player character to jump
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float jumpHeight;
	
};
