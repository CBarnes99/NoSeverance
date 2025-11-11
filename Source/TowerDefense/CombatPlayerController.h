// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <EnhancedInputLibrary.h>
#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "CombatPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartWaveSigniture);

UCLASS()
class TOWERDEFENSE_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "References")
	class AEnemySpawner* enemySpawner;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FStartWaveSigniture StartWaveEvent;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerCharacter* myPlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDataTable* turretDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int dataTableSize;

	UFUNCTION(BlueprintCallable)
	void UpdateHotbarSelection();

	UFUNCTION(BlueprintCallable)
	void UseCombatMappingContext(bool confirm);

	UFUNCTION(BlueprintCallable)
	void HaveMappingContextsBeenAsigned();

	//Player Input Mapping Variables which are editable in BP to select the button inputs for each action
	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputMappingContext* defaultMappingContext;

	//Player Input Mapping Variables which are editable in BP to select the button inputs for each action
	UPROPERTY(EditAnywhere, Category = "Input_Combat")
	class UInputMappingContext* combatMappingContext;

	//Player Input Mapping Variables which are editable in BP to select the button inputs for each action
	UPROPERTY(EditAnywhere, Category = "Input_Turret")
	class UInputMappingContext* turretMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputAction* moveActionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputAction* lookActionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputAction* jumpActionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputAction* runActionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputAction* startEnemyWaveActionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Combat")
	class UInputAction* attackActionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Default")
	class UInputAction* scrollWheelSelectionInput;

	UPROPERTY(EditAnywhere, Category = "Input_Turret")
	class UInputAction* confirmTurretPlacementInput;

	UPROPERTY(EditAnywhere, Category = "Input_Turret")
	class UInputAction* rotateTurretRightInput; 
	
	UPROPERTY(EditAnywhere, Category = "Input_Turret")
	class UInputAction* rotateTurretLeftInput;


	//Input Actions Functions
	UFUNCTION(BlueprintCallable)
	void MovementAction(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void MouseLookAction(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void RunningAction();

	UFUNCTION(BlueprintCallable)
	void RunningActionStop();

	UFUNCTION(BlueprintCallable)
	void CallGameModeToStartSpawningEnemies();

	UFUNCTION(BlueprintCallable)
	void JumpAction();

	UFUNCTION(BlueprintCallable)
	void StopJumpingAction();

	UFUNCTION(BlueprintCallable)
	void AttackAction();

	UFUNCTION(BlueprintCallable)
	void ScrollWheelSelectionAction(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void ConfirmTurretPlacementAction();

	UFUNCTION(BlueprintCallable)
	void RotateTurret(const FInputActionValue& Value);
};
