#include "EnemyAIController.h"
#include "EnemyCharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	senseSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sense Sight"));
	senseSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	senseSightConfig->SightRadius = 1500.f;
	senseSightConfig->LoseSightRadius = 2000.f;
	senseSightConfig->SightRadius = 120.f;
	

	senseSightConfig->PointOfViewBackwardOffset = 300.f;    // Push back perception start point
	senseSightConfig->NearClippingRadius = 400.f;           // Allow close-range detection

	AIPerceptionComponent->ConfigureSense(*senseSightConfig);
	AIPerceptionComponent->SetDominantSense(senseSightConfig->GetSenseImplementation());

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
		behaviorTree = Enemy->GetBehaviourTree();
		//if (UBehaviorTree* const Tree = Enemy->GetBehaviourTree())
		if (behaviorTree)
		{
			//UBlackboardComponent* b;
			//UseBlackboard(Tree->BlackboardAsset, AIBlackboard);
			UseBlackboard(behaviorTree->BlackboardAsset, AIBlackboard);
			Blackboard = AIBlackboard;
			//RunBehaviorTree(Tree);
			RunBehaviorTree(behaviorTree);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BLACKBOARD NULL IN ENEMY AI CONTROLLER - %s"), *this->GetName());
		}

		Enemy->OnDisableEvent.BindUObject(this, &AEnemyAIController::DisableAIController);

	}
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus)
{
	if (!actor->Tags.Contains(FName("Player")))
	{
		UE_LOG(LogTemp, Error, TEXT("TEST"));
		return;
	}

	if (stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Sensed = %s"), *actor->GetName());
		AIBlackboard->SetValueAsBool("bCanSeePlayer", true);
		AIBlackboard->SetValueAsObject("PlayerActor", actor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No longer Sense - %s"), *actor->GetName());
		AIBlackboard->SetValueAsBool("bCanSeePlayer", false);
		AIBlackboard->SetValueAsObject("PlayerActor", nullptr);
	}
}

void AEnemyAIController::DisableAIController()
{
	UBrainComponent* BrainComp = this->GetBrainComponent();
		if (BrainComp)
		{
			UBehaviorTreeComponent* BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComp);
			if (BehaviorComp)
			{
				BehaviorComp->StopTree(EBTStopMode::Forced);  // Stop the behavior tree safely
				BehaviorComp->Cleanup(); // Clean up the behavior tree component

				Blackboard->SetValueAsBool("bHasReachedNode", true);
			}
		}
}
