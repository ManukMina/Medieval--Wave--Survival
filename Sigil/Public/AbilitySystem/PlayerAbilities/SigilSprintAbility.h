// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SigilPlayerAbility.h"
#include "SigilSprintAbility.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilSprintAbility : public USigilPlayerAbility
{
	GENERATED_BODY()

	USigilSprintAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
};
