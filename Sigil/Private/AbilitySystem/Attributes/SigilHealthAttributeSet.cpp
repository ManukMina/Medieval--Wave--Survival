// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "AbilitySystem/Attributes/SigilHealthAttributeSet.h"

#include "GameplayEffectExtension.h"

USigilHealthAttributeSet::USigilHealthAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void USigilHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

	if (Attribute == GetHealthAttribute()){}
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	
	Super::PreAttributeChange(Attribute, NewValue);
}

void USigilHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		OnHealthChanged.Broadcast(this, OldValue, NewValue);
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		const float CurrentHealth = GetHealth();
		OnHealthChanged.Broadcast(this, CurrentHealth, CurrentHealth);
	}
}

void USigilHealthAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{

		const float DamageValue = GetDamage();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();
		const float NewHealth = FMath::Clamp(OldHealthValue - DamageValue, 0.0f, MaxHealthValue);

		if (OldHealthValue != NewHealth)
		{
			SetHealth(NewHealth);
		}

		SetDamage(0.0);
	}
}

