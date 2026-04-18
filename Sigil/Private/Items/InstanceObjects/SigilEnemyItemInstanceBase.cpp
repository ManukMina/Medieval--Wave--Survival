// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/InstanceObjects/SigilEnemyItemInstanceBase.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Character.h"
#include "Items/SigilItemBase.h"
#include "Items/Specs/SigilEnemyWeaponSpec.h"


void USigilEnemyItemInstanceBase::SpawnAndAttachItem(AActor* InOwner)
{
    if (!ItemSpec || !InOwner) return;
    
    USigilEnemyWeaponSpec* EnemySpec = Cast<USigilEnemyWeaponSpec>(ItemSpec);
    if (!EnemySpec) return;

    FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
    StreamableManager.RequestAsyncLoad(EnemySpec->WeaponClass.ToSoftObjectPath(),
        FStreamableDelegate::CreateWeakLambda(this, [this, InOwner, EnemySpec]()
        {
            if (!IsValid(InOwner)) return;
            UClass* LoadedItemClass = EnemySpec->WeaponClass.Get();
            if (!LoadedItemClass) return;

            FActorSpawnParameters Params;
            Params.Owner = InOwner;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            SpawnedActor = InOwner->GetWorld()->SpawnActor<ASigilItemBase>(LoadedItemClass, Params);

            if (const ACharacter* Character = Cast<ACharacter>(InOwner))
            {
                if (USkeletalMeshComponent* Mesh = Character->GetMesh())
                {
                    SpawnedActor->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, EnemySpec->AttachSocket);
                }
            }
        }));
}
