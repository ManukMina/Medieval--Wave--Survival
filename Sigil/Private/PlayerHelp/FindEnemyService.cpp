#include "FindEnemyService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = TEXT("Find Enemy (C++)");
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	APawn* SelfPawn = AIController->GetPawn();
	if (!SelfPawn)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	if (!EnemyClass)
	{
		BlackboardComp->ClearValue(BlackboardKey.SelectedKeyName);
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(SelfPawn->GetWorld(), EnemyClass, FoundActors);

	AActor* BestTarget = nullptr;
	float BestDistanceSq = TNumericLimits<float>::Max();

	for (AActor* Actor : FoundActors)
	{
		if (!Actor)
		{
			continue;
		}

		if (Actor == SelfPawn)
		{
			continue;
		}

		if (Actor->IsActorBeingDestroyed())
		{
			continue;
		}

		const float DistanceSq = FVector::DistSquared(
			SelfPawn->GetActorLocation(),
			Actor->GetActorLocation()
		);

		if (DistanceSq < BestDistanceSq)
		{
			BestDistanceSq = DistanceSq;
			BestTarget = Actor;
		}
	}

	if (BestTarget)
	{
		BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, BestTarget);
	}
	else
	{
		BlackboardComp->ClearValue(BlackboardKey.SelectedKeyName);
	}
}