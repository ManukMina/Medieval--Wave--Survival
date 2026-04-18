// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Utilities/SigilAnimUtils.h"
#include "SigilCharacterBase.generated.h"


class UPlayerItemAbilityManager;
class USigilCharacterStartupData;
class USigilAbilitySystemComponent;
class USigilHealthAttributeSet;

UCLASS()
class SIGIL_API ASigilCharacterBase : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilCharacterBase();

	//~ Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
	virtual void PossessedBy(AController* NewController) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character|AbilitySystem")
	TObjectPtr<USigilAbilitySystemComponent> SigilAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<USigilHealthAttributeSet> HealthAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sigil|StartupData")
	TSoftObjectPtr<USigilCharacterStartupData> StartupData;
	
	void GiveStartingAbilities();
	virtual void HandlePostStartupDataLoaded(USigilCharacterStartupData* LoadedStartupData) {};

public:
	UFUNCTION(BlueprintCallable, Category="Sigil|Character|Abilites|Tags")
	void AddGameplayTag(const FGameplayTag InTag);

	UFUNCTION(BlueprintCallable, Category="Sigil|Character|Abilites|Tags")
	void RemoveGameplayTag(const FGameplayTag InTag);
	
};
