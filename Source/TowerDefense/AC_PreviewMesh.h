#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_PreviewMesh.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAC_PreviewMesh : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_PreviewMesh();

	/**
	* @brief The Material for the actor for before it is placed into the world
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* outlineMaterial;

	/**
	* @brief The Material for the actor for when it is placed into the world
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* normalMaterial;

	/**
	* @brief Seting the outline material for a mesh
	* @param staticMesh The mesh you want to change to the outline material
	*/
	UFUNCTION(BlueprintCallable)
	void SetOutlineMaterial(UStaticMeshComponent* staticMesh);
	
	/**
	* @brief Seting the defualt material for a mesh
	* @param staticMesh The mesh you want to change to the default material
	*/
	UFUNCTION(BlueprintCallable)
	void SetDefaultMaterial(UStaticMeshComponent* staticMesh);

protected:

	virtual void BeginPlay() override;
};
