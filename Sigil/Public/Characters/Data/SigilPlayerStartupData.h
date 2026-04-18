// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilCharacterStartupData.h"
#include "AbilitySystem/Data/SigilInputAbilityData.h"
#include "SigilPlayerStartupData.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerStartupData : public USigilCharacterStartupData
{
	GENERATED_BODY()

public:
	virtual void GiveAbilityToComponent(USigilAbilitySystemComponent* InSigilAbilityComponent, int32 InAbilityLevel) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Sigil|StartupData|AbilitySet")
	TArray<FInputAbilitySet> PlayerStartupAbilities;
	
};
