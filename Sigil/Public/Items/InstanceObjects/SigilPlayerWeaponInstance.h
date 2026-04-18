// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/InstanceObjects/SigilPlayerSpawnedItemInstance.h"
#include "SigilPlayerWeaponInstance.generated.h"

class USigilPlayerWeaponSpec;
class ASigilPlayerWeapon;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerWeaponInstance : public USigilPlayerSpawnedItemInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<USigilPlayerWeaponSpec> PlayerWeaponSpec;
	
	UPROPERTY()
	TObjectPtr<ASigilPlayerWeapon> SpawnedWeapon;

	virtual void Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilAbilitySystemComponent) override;

	ASigilPlayerWeapon* GetSpawnedWeapon() const;
	
};
