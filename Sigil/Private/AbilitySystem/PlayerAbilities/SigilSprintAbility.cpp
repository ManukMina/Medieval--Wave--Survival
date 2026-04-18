// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "AbilitySystem/PlayerAbilities/SigilSprintAbility.h"

#include "Characters/SigilPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USigilSprintAbility::USigilSprintAbility()
{
	bActivateAbilityOnGranted = false;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationOwnedTags.AddTag(SigilGameplayTags::Ability_Movement_Sprinting);
	ActivationBlockedTags.AddTag(SigilGameplayTags::Ability_Movement_Airborne);
	
}

void USigilSprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	CommitAbility(Handle, ActorInfo, ActivationInfo);
	
	ASigilPlayerCharacter* PlayerCharacter = GetPlayerCharacterFromInfo();
	if(IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetMovementState(EMovementState::Jogging);
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 850.0f;
	}
	
}


void USigilSprintAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo)
{
	ASigilPlayerCharacter* PlayerCharacter = GetPlayerCharacterFromInfo();
	if(IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetMovementState(EMovementState::Walking);
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	
}
