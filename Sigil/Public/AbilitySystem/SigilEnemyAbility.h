// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilGameplayAbility.h"
#include "SigilEnemyAbility.generated.h"

class UPlayerItemAbilityManager;
class ASigilEnemyCharacter;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilEnemyAbility : public USigilGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	ASigilEnemyCharacter* GetEnemyCharacterFromInfo(); 

private:
	TWeakObjectPtr<ASigilEnemyCharacter> EnemyCharacterWeak;
};
