// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Controllers/SigilAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"


ASigilAIController::ASigilAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	SightSenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig"));

	SightSenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightSenseConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightSenseConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightSenseConfig->SightRadius = 6000.0f;
	SightSenseConfig->LoseSightRadius = 0.0f;
	SightSenseConfig->PeripheralVisionAngleDegrees = 360.0f;

	PerceptionComponent->ConfigureSense(*SightSenseConfig);
	PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	AAIController::SetGenericTeamId(FGenericTeamId(1));
	
}

void ASigilAIController::BeginPlay()
{
	Super::BeginPlay();
	if (UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComponent->SetCrowdSimulationState(bEnableCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		switch (CrowdAvoidanceQuality)
		{
		case 1: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;	
		case 2: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;	
		case 3: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;	
		case 4: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;	
		default:
			break;
		}

		CrowdComponent->SetAvoidanceGroup(1);
		CrowdComponent->SetGroupsToAvoid(1);
		CrowdComponent->SetCrowdCollisionQueryRange(CrowdAvoidanceRange);
	}
}

void ASigilAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(DefaultBehaviorTree.Get()))
	{
		RunBehaviorTree(DefaultBehaviorTree.Get());
	}	
}

ETeamAttitude::Type ASigilAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (IsValid(OtherPawn))
	{
		const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());
		if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId()< GetGenericTeamId())
		{
			return ETeamAttitude::Hostile;
		}
		return ETeamAttitude::Friendly;	
	}
	return ETeamAttitude::Neutral;	
}

void ASigilAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!IsValid(BlackboardComponent))
		return;

	if (IsValid(BlackboardComponent->GetValueAsObject((FName("TargetActor")))))
		return;

	// Once player is detected we never check for this again.
	if (Stimulus.WasSuccessfullySensed() && IsValid(Actor))	
		BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
}

