// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "AbilitySystem/Data/SigilInputAbilityData.h"
#include "AbilitySystem/SigilGameplayAbility.h"

bool FInputAbilitySet::IsValid() const
{
	return InputTag.IsValid() && Ability;
}
