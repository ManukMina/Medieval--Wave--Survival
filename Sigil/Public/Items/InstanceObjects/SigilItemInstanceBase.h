// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "UObject/Object.h"
#include "SigilItemInstanceBase.generated.h"


class USigilItemSpecBase;
class USigilAbilitySystemComponent;
class USigilPlayerItemSpecBase;

UCLASS()
class SIGIL_API USigilItemInstanceBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<USigilItemSpecBase> ItemSpec;

	UPROPERTY()
	TObjectPtr<USigilAbilitySystemComponent> OwningASC;

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> DefaultItemAbilitySpecHandles;

	UPROPERTY()
	TObjectPtr<AActor> SpawnedActor;

	virtual AActor* GetSpawnedActor() const { return SpawnedActor; }

	virtual void SpawnAndAttachItem(AActor* InOwner) {};
	virtual void Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilAbilitySystemComponent);
	virtual void GrantAbilities();
	virtual void RemoveAbilities();	
};
