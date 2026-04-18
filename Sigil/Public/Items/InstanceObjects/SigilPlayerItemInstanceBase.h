// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Items/InstanceObjects/SigilItemInstanceBase.h"
#include "SigilPlayerItemInstanceBase.generated.h"


class USigilAbilitySystemComponent;
class USigilPlayerItemSpecBase;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerItemInstanceBase : public USigilItemInstanceBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> ItemInputAbilitySpecHandles;

	UPROPERTY()
	USigilPlayerItemSpecBase* PlayerItemSpecBase;

	virtual void Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilAbilitySystemComponent) override;
	virtual void GrantAbilities() override;
	virtual void RemoveAbilities() override;
	
};
