// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SigilInputConfig.h"
#include "SigilInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIGIL_API USigilInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	
	template<class UserObject, typename FuncType>
	void BindNativeAction(const USigilInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* Object, FuncType Func);

	
template<class UserObject, typename FuncType>
	void BindAbilityAction(const USigilInputConfig* InInputConfig, UserObject* Object, FuncType PressedFunc, FuncType ReleasedFunc);
};

template <class UserObject, typename FuncType>
void USigilInputComponent::BindNativeAction(const USigilInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
	UserObject* Object, FuncType Func)
{
	check(InInputConfig);
	if(const UInputAction* Action = InInputConfig->GetInputActionByTag(InInputTag))
		BindAction(Action, TriggerEvent, Object, Func);
}

template <class UserObject, typename FuncType>
void USigilInputComponent::BindAbilityAction(const USigilInputConfig* InInputConfig, UserObject* Object, FuncType PressedFunc, FuncType ReleasedFunc)
{
	check(InInputConfig)
	for(const FSigilInputActionConfig& ActionConfig : InInputConfig->AbilityInputActions)
	{
		if(ActionConfig.InputAction && ActionConfig.InputTag.IsValid())
		{
			if(PressedFunc)
			{
				BindAction(ActionConfig.InputAction, ActionConfig.TriggerEvent, Object, PressedFunc, ActionConfig.InputTag);
			}
			
			if(ReleasedFunc)
			{
				BindAction(ActionConfig.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, ActionConfig.InputTag);
			}
		}
	}
}

