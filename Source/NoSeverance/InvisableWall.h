#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvisableWall.generated.h"

class UStaticMeshComponent;

UCLASS()
class NOSEVERANCE_API AInvisableWall : public AActor
{
	GENERATED_BODY()
	
public:	

	AInvisableWall();
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* invisableWallMesh;

};
