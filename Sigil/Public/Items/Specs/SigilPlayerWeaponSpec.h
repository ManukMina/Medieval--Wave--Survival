// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilPlayerSpawnedItemSpec.h"
#include "Items/InstanceObjects/SigilPlayerWeaponInstance.h"
#include "SigilPlayerWeaponSpec.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerWeaponSpec : public USigilPlayerSpawnedItemSpec
{
	GENERATED_BODY()
	
public:
	IMPLEMENT_ITEM_FACTORY(USigilPlayerWeaponInstance)
};
