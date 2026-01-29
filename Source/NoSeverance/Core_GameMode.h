#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core_GameMode.generated.h"

class ASpawnerManager;
class ACore_PlayerController;

DECLARE_MULTICAST_DELEGATE(FLevelCompleteSigniture)
DECLARE_MULTICAST_DELEGATE(FWaveDefeatedSigniture)
DECLARE_MULTICAST_DELEGATE(FNewWaveStartedSigniture)
DECLARE_DELEGATE_OneParam(FLastWaveSigniture, int /* Last Wave */)
DECLARE_DELEGATE_OneParam(FAmountOfEnmiesWithinARoundSigiture, int /* Last Wave */)
DECLARE_MULTICAST_DELEGATE(FEnemyHasBeenDefeatedSigniture)

UCLASS()
class NOSEVERANCE_API ACore_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	ACore_GameMode();

	/** When the level is completed, this is called within PrepareNewWave() */
	FLevelCompleteSigniture LevelCompleteEvent;

	/** When you've defeated a wave but not the last wave, this is called within PrepareNewWave() */
	FWaveDefeatedSigniture WaveDefeatedEvent;

	/** Is called when a new wave has started, called within StartEnemyWave() */
	FNewWaveStartedSigniture NewWaveStartedEvent;

	/** When the last wave is caluclated within StartEnemyWave(), this is called to notifiy the UI */
	FLastWaveSigniture LastWaveEvent;

	/** Called when the amount of enemies in the round has been calculated and the called within AmountOfEnemiesWithinWave() */
	FAmountOfEnmiesWithinARoundSigiture AmountOfEnemiesWithinARoundEvent;

	/** Called when the delegate within the spawner manager is called so the game mode can no notifiy other things */
	FEnemyHasBeenDefeatedSigniture EnemyHasBeenDefeatedEvent;

protected:

	virtual void BeginPlay() override;

	/** The spawner manager in the level */
	UPROPERTY(VisibleAnywhere)
	ASpawnerManager* spawnerManager;

	/** The current wave the level is on, starts at 0 on begin play */
	UPROPERTY(VisibleAnywhere)
	int currentWave;

	/** This is called when the player calls to start the next */
	UFUNCTION(BlueprintCallable)
	void StartEnemyWave();

	/** The final wave in the level, is set in StartEnemyWave() */
	UPROPERTY(VisibleAnywhere)
	int lastWave;

	/** The player controller used during combat */
	UPROPERTY(VisibleAnywhere)
	ACore_PlayerController* corePlayerController;

	/** Checks if theres a new wave or if you've finished the last wave */
	UFUNCTION(BlueprintCallable)
	void PrepareNewWave();

	/** Called when the player has been defeated or respawned
	* @param bDefeatedState true = player is defeated, false = player has respawned 
	* @param playerRespawnTime Unnecessary for this function, doesn't get used */
	UFUNCTION(BlueprintCallable)
	void OnPlayerDeathStateChange(bool bDefeatedState, float playerRespawnTime);

	UFUNCTION(BlueprintCallable)
	void AmountOfEnemiesWithinWave(int amount);

	UFUNCTION(BlueprintCallable)
	void EnemyHasBeenDefeated();
};
