// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilCharacterBase.h"
#include "SigilEnemyCharacter.generated.h"

class UEnemyItemAbilityManager;
class ASpawnEnemy;
UCLASS()
class SIGIL_API ASigilEnemyCharacter : public ASigilCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilEnemyCharacter();

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Sigil|Item|Abilities")
	UEnemyItemAbilityManager* GetItemAbilityManagerComponent() {return EnemyItemManager;}

	UPROPERTY(BlueprintReadWrite, Category="Wave")
  ASpawnEnemy* SpawnEnemyManager = nullptr;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character|Item|Abilities")
	TObjectPtr<UEnemyItemAbilityManager> EnemyItemManager;
	
	virtual void HandlePostStartupDataLoaded(USigilCharacterStartupData* LoadedStartupData) override;

	UFUNCTION()
	void HandleGameReady();
};
