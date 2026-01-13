#include "N_DeathAnimationStarted.h"
#include "EnemyCharacterBase.h"

void UN_DeathAnimationStarted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Notify: NO MESH WITHIN - %s"), *this->GetName());
		return;
	}

	AEnemyCharacterBase* enemy = Cast<AEnemyCharacterBase>(MeshComp->GetOwner());
	
	if (!enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Notify: ENEMY CAST FAILED WITHIN - %s"), *this->GetName());
		return;
	}

	enemy->OnDeathAnimationStarted();
}
