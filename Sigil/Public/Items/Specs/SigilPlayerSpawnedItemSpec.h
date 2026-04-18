// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilPlayerItemSpecBase.h"
#include "Items/InstanceObjects/SigilPlayerSpawnedItemInstance.h"
#include "SigilPlayerSpawnedItemSpec.generated.h"

class ASigilItemBase;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerSpawnedItemSpec : public USigilPlayerItemSpecBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Object Class")
	TSoftClassPtr<ASigilItemBase> ItemClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equip")
	FInputAbilitySet EquipAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equip")
	FName PassiveSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equip")
	FName ActiveSocket;

	IMPLEMENT_ITEM_FACTORY(USigilPlayerSpawnedItemInstance);

};
