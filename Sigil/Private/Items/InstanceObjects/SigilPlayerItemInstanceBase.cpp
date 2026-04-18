// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/InstanceObjects/SigilPlayerItemInstanceBase.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/Data/SigilInputAbilityData.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Items/Specs/SigilPlayerItemSpecBase.h"


void USigilPlayerItemInstanceBase::Initialize(USigilItemSpecBase* InItemSpec,
	USigilAbilitySystemComponent* SigilAbilitySystemComponent)
{
	Super::Initialize(InItemSpec, SigilAbilitySystemComponent);
	PlayerItemSpecBase = Cast<USigilPlayerItemSpecBase>(InItemSpec);
}

void USigilPlayerItemInstanceBase::GrantAbilities()
{
	Super::GrantAbilities();
	if (!OwningASC) return;

	for (const FInputAbilitySet& AbilitySet : PlayerItemSpecBase->ItemInputAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec Spec(AbilitySet.Ability, 1, INDEX_NONE, OwningASC->GetAvatarActor());
		Spec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		ItemInputAbilitySpecHandles.Add(OwningASC->GiveAbility(Spec));
	}
}

void USigilPlayerItemInstanceBase::RemoveAbilities()
{
	Super::RemoveAbilities();
	if (!OwningASC) return;

	for (FGameplayAbilitySpecHandle& ItemAbilityHandle : ItemInputAbilitySpecHandles)
	{
		if (ItemAbilityHandle.IsValid())
			OwningASC->ClearAbility(ItemAbilityHandle);
	}

	ItemInputAbilitySpecHandles.Empty();
}
