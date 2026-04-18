// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once
#include "GameplayTagContainer.h"
#include "SigilInputAbilityData.generated.h"

class USigilGameplayAbility;

USTRUCT(BlueprintType)
struct FInputAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ExposeFunctionCategories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USigilGameplayAbility> Ability;

	bool IsValid() const;
};

