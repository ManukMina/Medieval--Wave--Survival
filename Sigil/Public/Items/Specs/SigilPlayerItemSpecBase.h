// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilItemSpecBase.h"
#include "AbilitySystem/Data/SigilInputAbilityData.h"
#include "Engine/DataAsset.h"
#include "Items/InstanceObjects/SigilPlayerItemInstanceBase.h"
#include "SigilPlayerItemSpecBase.generated.h"

class USigilItemInstanceBase;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerItemSpecBase : public USigilItemSpecBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<FInputAbilitySet> ItemInputAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	IMPLEMENT_ITEM_FACTORY(USigilPlayerItemInstanceBase)

};
