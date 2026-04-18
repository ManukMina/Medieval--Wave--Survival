// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Components/ItemAbilityManagerBase.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Characters/SigilCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Items/SigilItemBase.h"
#include "Items/InstanceObjects/SigilItemInstanceBase.h"
#include "Items/Specs/SigilItemSpecBase.h"


// Sets default values for this component's properties
UItemAbilityManagerBase::UItemAbilityManagerBase()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentItemTag = FGameplayTag();
}

void UItemAbilityManagerBase::BeginPlay()
{
	Super::BeginPlay();
	if (AActor* Owner = GetOwner())
	{
		SigilCharacter = Cast<ASigilCharacterBase>(Owner);
		if (SigilCharacter)
		{
			OwnerSkeletalMesh = SigilCharacter->GetMesh();
			SigilAbilitySystemComponent = Cast<USigilAbilitySystemComponent>(SigilCharacter->GetAbilitySystemComponent());
		}
	}
}

void UItemAbilityManagerBase::SetCollisionForActiveItem(const bool bEnabled)
{
	if (const ASigilItemBase* SpawnedItem = GetSpawnedItemAs<ASigilItemBase>())
	{
		SpawnedItem->SetItemCollision(bEnabled);
	}
}

USigilItemInstanceBase* UItemAbilityManagerBase::GetItemInstance(const FGameplayTag InItemTag) const
{
	if (USigilItemInstanceBase* FoundInstance = CurrentItemMap.Find(InItemTag)->Get())
	{
		return FoundInstance;
	}
	return nullptr;
}

