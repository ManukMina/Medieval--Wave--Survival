// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "SigilCharacterStartupData.generated.h"


class USigilItemSpecBase;
class UItemAbilityManagerBase;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilCharacterStartupData : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveAbilityToComponent(USigilAbilitySystemComponent* InSigilAbilityComponent, int32 InAbilityLevel=1);
	virtual void GiveStartingItems(UItemAbilityManagerBase* InSigilAbilityManagerComponent);
	
protected:
	// Startup Abilities
	UPROPERTY(EditDefaultsOnly, Category="Sigil|StartupData")
	TArray<TSubclassOf<USigilGameplayAbility>> StartupAbilities;
	
	// Hit React / Death
	UPROPERTY(EditDefaultsOnly, Category="Sigil|StartupData")
	TArray<TSubclassOf<USigilGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category="Sigil|StartupData|StartingItems")
	TArray<TObjectPtr<USigilItemSpecBase>> StartingItems;
	
	virtual void CreateItemInstances(TArray<TObjectPtr<USigilItemSpecBase>>& InStartingItems, UItemAbilityManagerBase* ItemAbilityManager);
	void GiveAbilities(TArray<TSubclassOf<USigilGameplayAbility>>& AbilitiesToGive, USigilAbilitySystemComponent* InSigilAbilityComponent, int32 ApplyLevel=1);
	
};
