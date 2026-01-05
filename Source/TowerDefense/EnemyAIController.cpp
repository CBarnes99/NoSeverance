#include "EnemyAIController.h"
#include "EnemyCharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

AEnemyAIController::AEnemyAIController()
{

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	senseSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sense Sight"));
	senseSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	senseSightConfig->SightRadius = 500.f;
	senseSightConfig->LoseSightRadius = 650.f;
	senseSightConfig->SightRadius = 150.f;
	
	AIPerceptionComponent->ConfigureSense(*senseSightConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Perception Component NOT SET UP CORRECTLY WITHIN - %s"), *this->GetName());
	}
}


void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	//Asign the blackboard to the behaviour tree
	if (AEnemyCharacterBase* const Enemy = Cast<AEnemyCharacterBase>(InPawn))
	{
		if (UBehaviorTree* const Tree = Enemy->GetBehaviourTree())
		{
			//UBlackboardComponent* b;
			UseBlackboard(Tree->BlackboardAsset, AIBlackboard);
			Blackboard = AIBlackboard;
			RunBehaviorTree(Tree);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BLACKBOARD NULL IN ENEMY AI CONTROLLER - %s"), *this->GetName());
		}
	}
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus)
{
	if (stimulus.WasSuccessfullySensed() && actor->Tags.Contains(FName("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Sensed = %s, from - %s"), *actor->GetName(), *this->GetName());
	}
	else if(actor->Tags.Contains(FName("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("No longer Sense - %s"), *actor->GetName());
	}
}
