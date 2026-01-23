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
	levelUnlockedCheck.Add(level);
}

TSet<int> USaveGame_NoSeverance::GetLevelUnlockedCheck()
{
	return levelUnlockedCheck;
}
