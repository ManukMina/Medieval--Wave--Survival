// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilPlayerItemInstanceBase.h"
#include "SigilPlayerSpawnedItemInstance.generated.h"


class USigilPlayerSpawnedItemSpec;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerSpawnedItemInstance : public USigilPlayerItemInstanceBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	USigilPlayerSpawnedItemSpec* SpawnedItemSpec;
	
	UPROPERTY()
	FGameplayAbilitySpecHandle EquipAbilitySpecHandle;
	
	virtual void Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilAbilitySystemComponent) override;
	virtual void GrantEquipAbility();
	virtual void RemoveEquipAbility();
	virtual void SpawnAndAttachItem(AActor* InOwner) override;
};
