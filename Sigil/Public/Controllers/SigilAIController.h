// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/DetourCrowdAIController.h"
#include "SigilAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;

UCLASS()
class SIGIL_API ASigilAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()

public:
	ASigilAIController();
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	//~ Begin IGenericTeamAgentInterface Interface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~ End IGenericTeamAgentInterface Interface


	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> SightSenseConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> DefaultBehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, Category ="Crowd Avoidance Config")
	bool bEnableCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category ="Crowd Avoidance Config", meta = (EditCondition = "bEnableCrowdAvoidance",  UIMin ="1", UIMax ="4"))
	int32 CrowdAvoidanceQuality = 2;

	UPROPERTY(EditDefaultsOnly, Category ="Crowd Avoidance Config", meta = (EditCondition = "bEnableCrowdAvoidance"))
	float  CrowdAvoidanceRange = 600.0f;
	
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
