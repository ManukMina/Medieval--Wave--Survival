// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SigilGameplayAbility.generated.h"

class USigilAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sigil|AbilitySystem")
	bool bActivateAbilityOnGranted = false;
	
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	USigilAbilitySystemComponent* GetOwnerAbilitySystemComponent();	
};
