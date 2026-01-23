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
	void SaveUnlockedLevel(int level);

	UFUNCTION(BlueprintCallable)
	bool IsLevelUnlocked(int level);

protected:
	
	UCore_GameInstance();

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

};
