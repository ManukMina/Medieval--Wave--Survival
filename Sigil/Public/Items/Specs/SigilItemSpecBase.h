// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "Items/InstanceObjects/SigilItemInstanceBase.h"
#include "SigilItemSpecBase.generated.h"

class USigilPlayerItemInstanceBase;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilItemSpecBase : public UDataAsset
{
	GENERATED_BODY()

public:
	// Use item factory macro to reduce boilerplate:
	#define IMPLEMENT_ITEM_FACTORY(InstanceClass) \
	virtual USigilItemInstanceBase* CreateItemInstance(UObject* Outer) const override \
	{ \
	    return NewObject<InstanceClass>(Outer); \
	}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tag")
	FGameplayTag ItemTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<USigilGameplayAbility>> ItemDefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffects")
	TArray<TObjectPtr<UGameplayEffect>> ItemDefaultEffects;	
	
	// Factory method
	virtual USigilItemInstanceBase* CreateItemInstance(UObject* Outer) const;	
};
