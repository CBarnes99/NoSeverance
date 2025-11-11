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
	ATurretStatic* SpawnTurretByRow(int rowIndex);

	UFUNCTION(BlueprintCallable)
	void UpdatePreviewTurretLocation(FVector placeTurretLoc, int turretIndex);

	UFUNCTION(BlueprintCallable)
	void DisablePreviewTurret(ATurretStatic* turret);

	UFUNCTION(BlueprintCallable)
	void EnablePreviewTurret(ATurretStatic* turret);

	UFUNCTION(BlueprintCallable)
	void NoLongerPlacingTurrets();

	UFUNCTION(BlueprintCallable)
	bool GetisPreviewTurretActive();

	UFUNCTION(BlueprintCallable)
	void RotatePreviewTurret(float dir);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* turretDataTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<FName> dataTableRowNames;

	UFUNCTION(BlueprintCallable)
	void PoolAllPreivewTurrets();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<ATurretStatic*> pooledPreviewTurrets;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	int currentPreviewTurretIndex;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	//int previousPreviewTurretSelection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool isPreviewTurretActive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<ATurretStatic*> allPlacedTurrets;
	};
