// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SigilInputConfig.generated.h"


class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FSigilInputActionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETriggerEvent TriggerEvent = ETriggerEvent::Triggered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ExposeFunctionCategories="InputTag"))
	FGameplayTag InputTag;
};


UCLASS()
class SIGIL_API USigilInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ExposeFunctionCategories="InputTag"))
	TArray<FSigilInputActionConfig> SigilInputActions;
	
	TObjectPtr<UInputAction> GetInputActionByTag(const FGameplayTag& InInputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ExposeFunctionCategories="InputTag"))
	TArray<FSigilInputActionConfig> AbilityInputActions;
};
