// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/InstanceObjects//SigilPlayerWeaponInstance.h"
#include "Items/Specs/SigilPlayerWeaponSpec.h"
#include "Items/Weapons/SigilPlayerWeapon.h"

void USigilPlayerWeaponInstance::Initialize(USigilItemSpecBase* InItemSpec,
	USigilAbilitySystemComponent* SigilAbilitySystemComponent)
{
	Super::Initialize(InItemSpec, SigilAbilitySystemComponent);
	PlayerWeaponSpec = Cast<USigilPlayerWeaponSpec>(InItemSpec);
}

ASigilPlayerWeapon* USigilPlayerWeaponInstance::GetSpawnedWeapon() const
{
	return Cast<ASigilPlayerWeapon>(GetSpawnedActor());
}
