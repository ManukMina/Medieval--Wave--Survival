// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "AbilitySystem/SigilEnemyAbility.h"

#include "Characters/SigilEnemyCharacter.h"

ASigilEnemyCharacter* USigilEnemyAbility::GetEnemyCharacterFromInfo()
{

	if (!EnemyCharacterWeak.IsValid())
	{
		EnemyCharacterWeak = Cast<ASigilEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return EnemyCharacterWeak.IsValid() ? EnemyCharacterWeak.Get() : nullptr;
	
}

