// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Components/PlayerItemAbilityManager.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Characters/SigilPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Items/InstanceObjects/SigilPlayerSpawnedItemInstance.h"
#include  "Items/InstanceObjects/SigilItemInstanceBase.h"
#include "Items/Specs/SigilPlayerSpawnedItemSpec.h"



void UPlayerItemAbilityManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(SigilCharacter))
    {
		SigilPlayerCharacter = Cast<ASigilPlayerCharacter>(SigilCharacter);
		if (SigilPlayerCharacter)
		{
			if (APlayerController* PC = Cast<APlayerController>(SigilPlayerCharacter->GetInstigatorController()))
	        {
	            if (ULocalPlayer* LP = PC->GetLocalPlayer())
	            {
	                InputSubsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	            }
	        }
		}
    }
}

void UPlayerItemAbilityManager::CreateItemInstance(USigilItemSpecBase* InItemSpec)
{
	if (!InItemSpec || !SigilAbilitySystemComponent) return;

	USigilItemInstanceBase* Instance = InItemSpec->CreateItemInstance(this);
	Instance->Initialize(InItemSpec, SigilAbilitySystemComponent);

	//Optional If Instance is of Spawned type we need to do extra work
	if (USigilPlayerSpawnedItemInstance* SpawnedItem = Cast<USigilPlayerSpawnedItemInstance>(Instance))
	{
		SpawnedItem->SpawnAndAttachItem(GetOwner());
		SpawnedItem->GrantEquipAbility();
	}
	else
	{
		Instance->GrantAbilities();
	}
	
	CurrentItemMap.Add(InItemSpec->ItemTag, Instance);
}



void UPlayerItemAbilityManager::EquipItem(const FGameplayTag InItemTag)
{

	if (IsValid(CurrentActiveItem))
		UnequipItem();
	
	if (USigilPlayerSpawnedItemInstance* ItemToEquip = Cast<USigilPlayerSpawnedItemInstance>(CurrentItemMap.Find(InItemTag)->Get()))
	{
		if (IsValid(ItemToEquip))
		{
			ItemToEquip->SpawnedActor->AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ItemToEquip->SpawnedItemSpec->ActiveSocket);

			CurrentActiveItem = ItemToEquip;
			CurrentActiveItem->GrantAbilities();
			SigilAbilitySystemComponent->AddLooseGameplayTag(CurrentActiveItem->SpawnedItemSpec->ItemTag);
			InputSubsystem->AddMappingContext(CurrentActiveItem->SpawnedItemSpec->InputMappingContext, 1);
			CurrentItemTag = InItemTag;

		}
	}
}

void UPlayerItemAbilityManager::UnequipItem()
{
	if (!IsValid(CurrentActiveItem)) return;

	CurrentActiveItem->SpawnedActor->AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, CurrentActiveItem->SpawnedItemSpec->PassiveSocket);
	CurrentActiveItem->RemoveAbilities();
	SigilAbilitySystemComponent->RemoveLooseGameplayTag(CurrentActiveItem->SpawnedItemSpec->ItemTag);
	InputSubsystem->RemoveMappingContext(CurrentActiveItem->SpawnedItemSpec->InputMappingContext);
	SigilPlayerCharacter->SetLinkedLayerToDefault();
	CurrentActiveItem = nullptr;
	CurrentItemTag = FGameplayTag();
	
}

AActor* UPlayerItemAbilityManager::GetSpawnedItem() const
{
	return CurrentActiveItem ? CurrentActiveItem->SpawnedActor : nullptr;
}

