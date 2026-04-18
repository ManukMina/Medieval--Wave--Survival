// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/InstanceObjects/SigilEnemyItemInstanceBase.h"
#include "Items/Specs/SigilItemSpecBase.h"
#include "SigilEnemyWeaponSpec.generated.h"

class ASigilItemBase;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilEnemyWeaponSpec : public USigilItemSpecBase
{
	GENERATED_BODY()

public:
	IMPLEMENT_ITEM_FACTORY(USigilEnemyItemInstanceBase)

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSoftClassPtr<ASigilItemBase> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName AttachSocket;  // default socket

};
