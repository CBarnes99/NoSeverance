// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_PreviewMesh.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAC_PreviewMesh : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_PreviewMesh();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* outlineMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* normalMaterial;

	UFUNCTION(BlueprintCallable)
	void SetOutlineMaterial(UStaticMeshComponent* staticMesh);
	
	UFUNCTION(BlueprintCallable)
	void SetNormalMaterial(UStaticMeshComponent* staticMesh);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
