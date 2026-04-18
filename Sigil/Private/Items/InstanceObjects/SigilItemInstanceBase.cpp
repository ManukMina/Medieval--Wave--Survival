// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/InstanceObjects/SigilItemInstanceBase.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Items/Specs/SigilItemSpecBase.h"

void USigilItemInstanceBase::Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilAbilitySystemComponent)
{
	ItemSpec = InItemSpec;
	OwningASC = SigilAbilitySystemComponent;
}

void USigilItemInstanceBase::GrantAbilities()
{
	if (!OwningASC) return;

	for (TSubclassOf<USigilGameplayAbility>& DefaultAbility : ItemSpec->ItemDefaultAbilities)
	{
		if (!DefaultAbility) continue;

		FGameplayAbilitySpec Spec(DefaultAbility, 1, INDEX_NONE, OwningASC->GetAvatarActor());
		DefaultItemAbilitySpecHandles.Add(OwningASC->GiveAbility(Spec));
	}
}

void USigilItemInstanceBase::RemoveAbilities()
{
	if (!OwningASC) return;

	for (FGameplayAbilitySpecHandle& ItemAbilityHandle : DefaultItemAbilitySpecHandles)
	{
		if (ItemAbilityHandle.IsValid())
			OwningASC->ClearAbility(ItemAbilityHandle);
	}

	DefaultItemAbilitySpecHandles.Empty();
}
