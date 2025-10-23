// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "EngineUtils.h" 
#include "EnemySpawner.h"
#include "CombatGameMode.h"

void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Set defualt mapping context
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (defualtMappingContext)
			{
				Subsystem->AddMappingContext(defualtMappingContext, 0);
			}
		}
	}
}

void ACombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Binds the Input Actions assigned in the editor to the corisponding functions
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(moveActionInput, ETriggerEvent::Triggered, this, &ACombatPlayerController::MovementAction);

		Input->BindAction(lookActionInput, ETriggerEvent::Triggered, this, &ACombatPlayerController::MouseLookAction);

		Input->BindAction(jumpActionInput, ETriggerEvent::Started, this, &ACombatPlayerController::JumpAction);
		Input->BindAction(jumpActionInput, ETriggerEvent::Completed, this, &ACombatPlayerController::StopJumpingAction);

		Input->BindAction(runActionInput, ETriggerEvent::Triggered, this, &ACombatPlayerController::RunningAction);
		Input->BindAction(runActionInput, ETriggerEvent::Completed, this, &ACombatPlayerController::RunningActionStop);

		Input->BindAction(startEnemyWaveActionInput, ETriggerEvent::Triggered, this, &ACombatPlayerController::CallGameModeToStartSpawningEnemies);

	}
}

void ACombatPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACombatPlayerController::MovementAction(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("WSAD"));

	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();

		const FVector Forward = MyCharacter->GetActorForwardVector();
		const FVector Right = MyCharacter->GetActorRightVector();

		MyCharacter->AddMovementInput(Forward, MovementVector.Y);
		MyCharacter->AddMovementInput(Right, MovementVector.X);
	}

}

void ACombatPlayerController::MouseLookAction(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Mouse"));

	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		const FVector2D LookAxisVector = Value.Get<FVector2D>();

		MyCharacter->AddControllerPitchInput(LookAxisVector.Y);
		MyCharacter->AddControllerYawInput(LookAxisVector.X);
	}
}

void ACombatPlayerController::RunningAction()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Shift"));

	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = MyCharacter->runSpeed;
	}
	
}

void ACombatPlayerController::RunningActionStop()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Shift"));

	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = MyCharacter->movementSpeed;
	}
}

void ACombatPlayerController::JumpAction()
{
	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		MyCharacter->Jump();
	}
}

void ACombatPlayerController::StopJumpingAction()
{
	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		MyCharacter->StopJumping();
	}
}


void ACombatPlayerController::CallGameModeToStartSpawningEnemies()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("ENTER PRESSED"));

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();

	ACombatGameMode* MyGameMode = Cast<ACombatGameMode>(GameModeBase);

	MyGameMode->StartEnemyWave();
};
