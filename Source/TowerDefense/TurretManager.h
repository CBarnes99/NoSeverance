#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretStatic.h"
#include "TurretManager.generated.h"

UCLASS()
class TOWERDEFENSE_API ATurretManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ATurretStatic* SpawnTurretByRow(int rowIndex, FVector spawnLoc, FRotator spawnRot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDataTable* turretDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<FName> dataTableRowNames;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	ATurretStatic* previewTurretActor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<ATurretStatic*> allTurrets;
	};
