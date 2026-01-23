#include "Core_GameInstance.h"
#include "SaveGame_NoSeverance.h"
#include "Kismet/GameplayStatics.h"

UCore_GameInstance::UCore_GameInstance()
{
	saveSlotName = "SaveSlot1";
	userIndex = 0;

	LoadGame();
}

void UCore_GameInstance::LoadGame()
{
	UE_LOG(LogTemp, Warning, TEXT("LoadGame: Load Game was called from the game instance!"));

	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &UCore_GameInstance::LoadGameCompleted);
	UGameplayStatics::AsyncLoadGameFromSlot(saveSlotName, userIndex, LoadedDelegate);
}

void UCore_GameInstance::LoadGameCompleted(const FString& slotName, const int32 loadedUserIndex, USaveGame* saveGame)
{
	UE_LOG(LogTemp, Warning, TEXT("LoadComplete: slotName = %s, User Index = %d, LoadedSaveGame = %s, Within - %s"), *slotName, loadedUserIndex, saveGame ? TEXT("True") : TEXT("False"), *this->GetName());
	if (saveGame)
	{
		SaveGameInstance = Cast<USaveGame_NoSeverance>(saveGame);
		if (!SaveGameInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("LoadComplete: CAST FAILED WHEN LOADING SAVE!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LoadComplete: SaveGameInstance IS INVALID, creating Save Game!"));
		SaveUnlockedLevel(1);

	}
}

void UCore_GameInstance::SaveUnlockedLevel(int level)
{
	if (SaveGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveUnlockedLevel: SaveGameInstance found, saving to instance!"));
		FAsyncSaveGameToSlotDelegate SavedDelegate;

		SavedDelegate.BindUObject(this, &UCore_GameInstance::SaveGameCompleted);

		SaveGameInstance->levelUnlockedCheck.Add(level, true);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, saveSlotName, userIndex, SavedDelegate);
	}
	else if (USaveGame_NoSeverance* SaveGame = Cast<USaveGame_NoSeverance>(UGameplayStatics::CreateSaveGameObject(USaveGame_NoSeverance::StaticClass())))
	{
		UE_LOG(LogTemp, Error, TEXT("SaveUnlockedLevel: SaveGameInstance NOT found, creating new save game!"));
		SaveGameInstance = SaveGame;

		FAsyncSaveGameToSlotDelegate SavedDelegate;

		SavedDelegate.BindUObject(this, &UCore_GameInstance::SaveGameCompleted);

		SaveGameInstance->levelUnlockedCheck.Add(level, true);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, saveSlotName, userIndex, SavedDelegate);
	}
}

void UCore_GameInstance::SaveGameCompleted(const FString& slotName, const int savedUserIndex, bool success)
{
	UE_LOG(LogTemp, Warning, TEXT("SaveComplete: slotName = %s, User Index = %d, Success = %s, Within - %s"), *slotName, savedUserIndex, success ? TEXT("True") : TEXT("False"), * this->GetName());
	//If need be, add a delegate and broadcast it to things that need to know the saving is complete.
}

bool UCore_GameInstance::IsLevelUnlocked(int level)
{
	if (!SaveGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("IsLevelUnlocked: SAVE GAME INSTANCE NOT FOUND WITHIN - %s"), *this->GetName());
		return false;
	}
	return SaveGameInstance->IsLevelUnlocked(level);
}