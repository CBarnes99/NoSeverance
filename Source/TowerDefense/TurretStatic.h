// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_TurretStats.h"
#include "TurretStatic.generated.h"

UCLASS()
class TOWERDEFENSE_API ATurretStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretStatic();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* turretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* collisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UArrowComponent* arrowComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Turret")
	UDA_TurretStats* turretStats;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Turret")
	float damageAmount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Turret")
	float activeTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Turret")
	float rechargeTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Turret")
	int cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSet<AActor*> damagedActors;

	//Will set up damage types later on
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	TSubclassOf<UDamageType> damageType;*/

	UFUNCTION(BlueprintCallable)
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult);

};
