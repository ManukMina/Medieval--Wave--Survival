// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Components/EnemyItemAbilityManager.h"
#include "Items/Specs/SigilItemSpecBase.h"

void UEnemyItemAbilityManager::CreateItemInstance(USigilItemSpecBase* InItemSpec)
{
	if (!InItemSpec || !SigilAbilitySystemComponent) return;

	USigilItemInstanceBase* Instance = InItemSpec->CreateItemInstance(this);
	Instance->Initialize(InItemSpec, SigilAbilitySystemComponent);
	Instance->SpawnAndAttachItem(GetOwner());
	Instance->GrantAbilities();
	
	CurrentActiveItem = Cast<USigilEnemyItemInstanceBase>(Instance);
	CurrentItemMap.Add(InItemSpec->ItemTag, Instance);
}

AActor* UEnemyItemAbilityManager::GetSpawnedItem() const
{
	return CurrentActiveItem->SpawnedActor.Get();
}



