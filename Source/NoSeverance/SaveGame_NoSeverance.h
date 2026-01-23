#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGame_NoSeverance.generated.h"

UCLASS()
class NOSEVERANCE_API USaveGame_NoSeverance : public USaveGame
{
	GENERATED_BODY()

public:
	USaveGame_NoSeverance();

	UFUNCTION(BlueprintCallable)
	bool IsLevelUnlocked(int level);

	UFUNCTION(BlueprintCallable)
	void UnlockLevel(int level);

	UFUNCTION(BlueprintCallable)
	TSet<int> GetLevelUnlockedCheck();

protected:

	UPROPERTY(VisibleAnywhere)
	TSet<int> levelUnlockedCheck;

};
