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

	UPROPERTY(VisibleAnywhere)
	TMap<int, bool> levelUnlockedCheck;

	UFUNCTION(BlueprintCallable)
	bool IsLevelUnlocked(int level);

};
