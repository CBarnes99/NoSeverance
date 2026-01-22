#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "N_MeleeAttack.generated.h"

UCLASS()
class NOSEVERANCE_API UN_MeleeAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
	FName attackSocketName;

	UPROPERTY(EditAnywhere)
	float traceRadius;

};
