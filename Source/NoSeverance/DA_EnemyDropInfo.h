#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "E_EnemyDrop.h"
#include "DA_EnemyDropInfo.generated.h"

UCLASS(Blueprintable)
class NOSEVERANCE_API UDA_EnemyDropInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EEnemyDrop, float> dropValues;
};
