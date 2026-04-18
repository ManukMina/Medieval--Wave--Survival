// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "FindEnemyService.generated.h"

UCLASS()
class SIGIL_API UFindEnemyService : public UBTService_BlackboardBase
{
		GENERATED_BODY()

	public:
		UFindEnemyService();

	protected:
		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	protected:
		UPROPERTY(EditAnywhere, Category = "Find Enemy")
		TSubclassOf<AActor> EnemyClass;
	};