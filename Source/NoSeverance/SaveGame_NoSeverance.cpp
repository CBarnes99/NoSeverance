#include "SaveGame_NoSeverance.h"

USaveGame_NoSeverance::USaveGame_NoSeverance()
{
}

bool USaveGame_NoSeverance::IsLevelUnlocked(int level)
{
	if (levelUnlockedCheck.Contains(level))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void USaveGame_NoSeverance::UnlockLevel(int level)
{
	if (levelUnlockedCheck.Contains(level))
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlockLevel: Level %d is already unlocked"), level);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlockLevel: Unlocked level %d"), level);
		levelUnlockedCheck.Add(level);
	}
}

TSet<int> USaveGame_NoSeverance::GetLevelUnlockedCheck()
{
	return levelUnlockedCheck;
}
