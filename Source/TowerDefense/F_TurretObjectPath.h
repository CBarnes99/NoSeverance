#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TurretStatic.h"
#include "F_TurretObjectPath.generated.h"

USTRUCT(BlueprintType)
struct TOWERDEFENSE_API F_TurretObjectPath : public FTableRowBase
{
public:
	GENERATED_BODY()

	/** Turret Class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<ATurretStatic> turretClass;

};
