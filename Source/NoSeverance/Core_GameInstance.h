#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Core_GameInstance.generated.h"

class USaveGame_NoSeverance;

UCLASS()
class NOSEVERANCE_API UCore_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void UnlockSpecificLevel(int level);

	UFUNCTION(BlueprintCallable)
	void UnlockNextLevel();

	UFUNCTION(BlueprintCallable)
	bool IsLevelUnlocked(int level);

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevelInt(int level);

	UFUNCTION(BlueprintCallable)
	int GetCurrentLevelInt();

	UFUNCTION(BlueprintCallable)
	void DeleteSave();

protected:
	
	UCore_GameInstance();

	UFUNCTION(BlueprintCallable)
	void CreateSaveGame();

	UPROPERTY(VisibleAnywhere)
	FString saveSlotName;

	UPROPERTY(VisibleAnywhere)
	uint32 userIndex;

	UFUNCTION()
	void SaveGameCompleted(const FString& slotName, const int savedUserIndex, bool success);

	UFUNCTION()
	void LoadGameCompleted(const FString& slotName, const int32 loadedUserIndex, USaveGame* saveGame);

	UPROPERTY(VisibleAnywhere)
	USaveGame_NoSeverance* SaveGameInstance;

	UPROPERTY(VisibleAnywhere)
	int currentLevelInt;

};
