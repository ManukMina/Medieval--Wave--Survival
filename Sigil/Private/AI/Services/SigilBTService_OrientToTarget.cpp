// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "AI/Services/SigilBTService_OrientToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USigilBTService_OrientToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			{
				if (ensure(MyController))
				{
					APawn* AIPawn = MyController->GetPawn();
					if (ensure(AIPawn))
					{
						AIPawn->SetActorRotation(FMath::RInterpTo(AIPawn->GetActorRotation(),
							FRotationMatrix::MakeFromX(TargetActor->GetActorLocation() - AIPawn->GetActorLocation()).Rotator(),
							DeltaSeconds, RotationInterpSpeed));
					}
						
				}
			}
		}
	}
}
