// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Characters/Data/SigilCharacterStartupData.h"
#include "Items/Specs/SigilItemSpecBase.h"
#include "Components/ItemAbilityManagerBase.h"

void USigilCharacterStartupData::GiveAbilityToComponent(USigilAbilitySystemComponent* InSigilAbilityComponent, int32 InAbilityLevel)
{
	check(InSigilAbilityComponent)
	GiveAbilities(StartupAbilities, InSigilAbilityComponent, InAbilityLevel);
	GiveAbilities(ReactiveAbilities, InSigilAbilityComponent, InAbilityLevel);
}


void USigilCharacterStartupData::GiveAbilities(TArray<TSubclassOf<USigilGameplayAbility>>& AbilitiesToGive,
                                               USigilAbilitySystemComponent* InSigilAbilityComponent, int32 ApplyLevel)
{
	if(AbilitiesToGive.IsEmpty())
		return;

	for (const TSubclassOf<USigilGameplayAbility>& Ability : AbilitiesToGive)
	{
		if(!IsValid(Ability)) continue;
		InSigilAbilityComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, InSigilAbilityComponent->GetAvatarActor()));
	}
}

void USigilCharacterStartupData::GiveStartingItems(UItemAbilityManagerBase* InSigilAbilityManagerComponent)
{
	check(InSigilAbilityManagerComponent)
	CreateItemInstances(StartingItems, InSigilAbilityManagerComponent);
}

void USigilCharacterStartupData::CreateItemInstances(TArray<TObjectPtr<USigilItemSpecBase>>& InStartingItems,
	UItemAbilityManagerBase* ItemAbilityManager)
{
	if (InStartingItems.IsEmpty()) return;
	for (const TObjectPtr<USigilItemSpecBase>& Item : InStartingItems)
		ItemAbilityManager->CreateItemInstance(Item.Get());
}
