// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Input/SigilInputConfig.h"

TObjectPtr<UInputAction> USigilInputConfig::GetInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FSigilInputActionConfig& InputConfig : SigilInputActions)
	{
		if(IsValid(InputConfig.InputAction) && InputConfig.InputTag == InInputTag)
		{
			return InputConfig.InputAction;
		}
	}
	return nullptr;
}

