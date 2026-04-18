// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilGameplayAbility.h"
#include "SigilPlayerAbility.generated.h"

class UPlayerItemAbilityManager;
class ASigilPlayerController;
class ASigilPlayerCharacter;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerAbility : public USigilGameplayAbility
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	ASigilPlayerCharacter* GetPlayerCharacterFromInfo(); 
	
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	ASigilPlayerController* GetPlayerControllerFromInfo();

	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	UPlayerItemAbilityManager* GetItemAbilityManagerFromInfo();
	
private:
	TWeakObjectPtr<ASigilPlayerCharacter> PlayerCharacterWeak;
	TWeakObjectPtr<ASigilPlayerController> PlayerControllerWeak;
};
