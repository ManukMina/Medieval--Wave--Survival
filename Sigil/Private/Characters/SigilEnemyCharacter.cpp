// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Characters/SigilEnemyCharacter.h"

#include "Characters/Data/SigilCharacterStartupData.h"
#include "Components/EnemyItemAbilityManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameState/SigilBaseGameState.h"



// Sets default values
ASigilEnemyCharacter::ASigilEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::Disabled;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 435.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	EnemyItemManager = CreateDefaultSubobject<UEnemyItemAbilityManager>("EnemyItemAbilityManager");
	
}

void ASigilEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	ASigilBaseGameState* GameState = GetWorld()->GetGameState<ASigilBaseGameState>();
	if (GameState)
	{
		if (!GameState->bIsGameReady)
		{
			GameState->GameReadyEvent.AddDynamic(this, &ASigilEnemyCharacter::HandleGameReady);
		}
		else
		{
			HandleGameReady();
		}
	}
}

// If the implementation for enemies / players never differ - move to base class
void ASigilEnemyCharacter::HandlePostStartupDataLoaded(USigilCharacterStartupData* LoadedStartupData)
{
    if (!IsValid(LoadedStartupData)) return;
	LoadedStartupData->GiveStartingItems(EnemyItemManager);
}

void ASigilEnemyCharacter::HandleGameReady()
{
	if (!IsValid(Controller))
	{
		SpawnDefaultController();
	}
}

