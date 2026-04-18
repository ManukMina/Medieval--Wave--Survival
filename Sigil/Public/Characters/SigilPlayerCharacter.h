// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilCharacterBase.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Data/SigilCharacterStartupData.h"
#include "Data/SigilPlayerStartupData.h"
#include "GameplayTags/SigilGameplayTagsAbilities.h"
#include "SigilPlayerCharacter.generated.h"

class USigilInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SIGIL_API ASigilPlayerCharacter : public ASigilCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilPlayerCharacter();
	
	virtual void PossessedBy(AController* NewController) override;

	void UnlockHeavyAttack();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character", meta=(AllowPrivateAccess="True"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character", meta=(AllowPrivateAccess="True"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sigil|Character|Input", meta=(AllowPrivateAccess="True"))
	TObjectPtr<USigilInputConfig> InputConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character|Item|Abilities")
	TObjectPtr<UPlayerItemAbilityManager> ItemAbilityManagerComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sigil|Animation", meta=(AllowPrivateAccess=true))
	EMovementState MovementState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sigil|Character|Input", meta=(AllowPrivateAccess="True"))
	TSubclassOf<UAnimInstance> AnimLayerClass;

	UPROPERTY(BlueprintReadOnly) bool bHeavyUnlocked = false;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	
	virtual void HandlePostStartupDataLoaded(USigilCharacterStartupData* LoadedStartupData) override;
	void OnMovementModeChanged(const EMovementMode PrevMovementMode, const uint8 PreviousCustomMode = 0);	
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Sigil|Item|Abilities")
	UPlayerItemAbilityManager* GetItemAbilityManagerComponent() {return ItemAbilityManagerComponent;}
	
	UFUNCTION(BlueprintCallable, Category="Sigil|Animation")
	void SetMovementState(const EMovementState InMovementState);

	UFUNCTION(BlueprintPure, Category="Sigil|Animation")
	EMovementState GetMovementState() const {return MovementState;}

	UFUNCTION(BlueprintCallable, Category="Sigil|Character|Animation")
	void SetLinkedLayerToDefault();
};




