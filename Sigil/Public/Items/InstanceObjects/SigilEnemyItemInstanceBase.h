// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilItemInstanceBase.h"
#include "SigilEnemyItemInstanceBase.generated.h"

class USigilEnemyWeaponSpec;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilEnemyItemInstanceBase : public USigilItemInstanceBase
{
	GENERATED_BODY()

public:
	virtual void SpawnAndAttachItem(AActor* InOwner) override;
};
