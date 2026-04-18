// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Characters/SigilCharacterBase.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/SigilHealthAttributeSet.h"
#include "Characters/Data/SigilCharacterStartupData.h"
#include "Engine/AssetManager.h"
#include "GameState/SigilBaseGameState.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASigilCharacterBase::ASigilCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;

	SigilAbilitySystemComponent = CreateDefaultSubobject<USigilAbilitySystemComponent>("SigilAbilitySystemComponent");
	HealthAttributeSet = CreateDefaultSubobject<USigilHealthAttributeSet>("HealthAttributeSet");
}

UAbilitySystemComponent* ASigilCharacterBase::GetAbilitySystemComponent() const
{
	return SigilAbilitySystemComponent.Get();
}


void ASigilCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SigilAbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveStartingAbilities();
}

void ASigilCharacterBase::GiveStartingAbilities()
{
	if(StartupData.IsNull())
		return;

	ASigilBaseGameState* GameState = GetWorld()->GetGameState<ASigilBaseGameState>();
	ensure(IsValid(GameState));

	GameState->RegisterLoad();
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(StartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, GameState]()
		{
			if (USigilCharacterStartupData* LoadedData = StartupData.Get())
			{
				LoadedData->GiveAbilityToComponent(SigilAbilitySystemComponent);
				HandlePostStartupDataLoaded(LoadedData);
			}

			if(IsValid(GameState))
				GameState->MarkLoadComplete();
		}));
}


void ASigilCharacterBase::AddGameplayTag(const FGameplayTag InTag)
{
		SigilAbilitySystemComponent->AddLooseGameplayTag(InTag);
}

void ASigilCharacterBase::RemoveGameplayTag(const FGameplayTag InTag)
{
		SigilAbilitySystemComponent->RemoveLooseGameplayTag(InTag);
}


