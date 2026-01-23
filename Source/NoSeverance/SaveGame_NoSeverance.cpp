#include "SaveGame_NoSeverance.h"

USaveGame_NoSeverance::USaveGame_NoSeverance()
{
	levelUnlockedCheck.Add(1, true);
}

bool USaveGame_NoSeverance::IsLevelUnlocked(int level)
{
	if (levelUnlockedCheck.Contains(level))
	{
		return *levelUnlockedCheck.Find(level);
	}
	return false;
}
