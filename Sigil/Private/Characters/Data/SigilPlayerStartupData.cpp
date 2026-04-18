// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Characters/Data/SigilPlayerStartupData.h"

void USigilPlayerStartupData::GiveAbilityToComponent(USigilAbilitySystemComponent* InSigilAbilityComponent, int32 InAbilityLevel)
{
	Super::GiveAbilityToComponent(InSigilAbilityComponent, InAbilityLevel);

	for(const FInputAbilitySet& AbilitySet : PlayerStartupAbilities)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.Ability, InAbilityLevel, INDEX_NONE, InSigilAbilityComponent->GetAvatarActor());
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		InSigilAbilityComponent->GiveAbility(AbilitySpec);
	}
	
}

