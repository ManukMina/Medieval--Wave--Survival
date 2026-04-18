// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/InstanceObjects/SigilPlayerSpawnedItemInstance.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Engine/AssetManager.h"
#include "GameFramework/Character.h"
#include "Items/SigilItemBase.h"
#include "Items/Specs/SigilPlayerSpawnedItemSpec.h"

void USigilPlayerSpawnedItemInstance::Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilAbilitySystemComponent)
{
	Super::Initialize(InItemSpec, SigilAbilitySystemComponent);
	SpawnedItemSpec = Cast<USigilPlayerSpawnedItemSpec>(InItemSpec);
}

void USigilPlayerSpawnedItemInstance::GrantEquipAbility()
{

	if (!SpawnedItemSpec || !OwningASC) return;

	if (SpawnedItemSpec->EquipAbility.IsValid())
	{
		FGameplayAbilitySpec Spec(SpawnedItemSpec->EquipAbility.Ability, 1, INDEX_NONE, OwningASC->GetAvatarActor());
		Spec.GetDynamicSpecSourceTags().AddTag(SpawnedItemSpec->EquipAbility.InputTag);
		EquipAbilitySpecHandle = OwningASC->GiveAbility(Spec);
	}
	
}

void USigilPlayerSpawnedItemInstance::RemoveEquipAbility()
{
	if (!OwningASC) return;


	if (EquipAbilitySpecHandle.IsValid())
		OwningASC->ClearAbility(EquipAbilitySpecHandle);

	EquipAbilitySpecHandle = FGameplayAbilitySpecHandle();
}

void USigilPlayerSpawnedItemInstance::SpawnAndAttachItem(AActor* InOwner)
{
	
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(SpawnedItemSpec->ItemClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateWeakLambda(this, [this, InOwner]()
		{
			if (!IsValid(InOwner)) return;
			
			UClass* LoadedItemClass = SpawnedItemSpec->ItemClass.Get();
			if (!LoadedItemClass) return;

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = InOwner;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnedActor = InOwner->GetWorld()->SpawnActor<ASigilItemBase>(LoadedItemClass, SpawnParameters);

			if (ACharacter* Character = Cast<ACharacter>(InOwner))
			{
				if (USkeletalMeshComponent* SkelMesh = Character->GetMesh())
				{
					SpawnedActor->AttachToComponent(SkelMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SpawnedItemSpec->PassiveSocket);
				}
			}
		}));
}