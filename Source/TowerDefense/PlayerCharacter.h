#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DA_CharacterStats.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TOWERDEFENSE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Player Stats, Edit in Blueprints Data Asset
	UPROPERTY(EditDefaultsOnly, Category = "PlayerStats")
	TObjectPtr<UDA_CharacterStats> PlayerInfo;

	UPROPERTY(EditAnywhere, Category = "PlayerStats")
	int MaxSpeed;

	UPROPERTY(EditAnywhere, Category = "PlayerStats")
	int JumpHeight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components added to player
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
};
