// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#pragma once

#include "NativeGameplayTags.h"

namespace SigilGameplayTags
{

	// Status Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Damage)  
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Heal)  
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Stunned)  
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Dead)  
	
	// Movement Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Sprinting)  
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Grounded) 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Airborne) 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Dodge) 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_DoubleJump)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Effect_Cooldown_Attack_Light_Staff)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Effect_Cooldown_Dodge)

	// Generic Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_BlockMontage)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_HitReact)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Weapon_Staff)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Weapon_Sword)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Weapon_Mace)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Weapon_Axe)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Weapon_Bow)

	// Staff Related
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Equip_Staff)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Light_Staff)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Heavy_Staff)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Event_AttackWindow)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Event_Equip_Staff)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Event_Unequip_Staff)
	

	//Enemies
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Light_Sword)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Heavy_Sword)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Light_Mace)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Heavy_Mace)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Light_Axe)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Heavy_Axe)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Ranged)

	
	
}
