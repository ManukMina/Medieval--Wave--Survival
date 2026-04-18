// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ItemAbilityManagerBase.h"
#include "GameplayTagContainer.h"
#include "PlayerItemAbilityManager.generated.h"

class USigilItemSpecBase;
class ASigilPlayerCharacter;
class USigilPlayerSpawnedItemInstance;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIGIL_API UPlayerItemAbilityManager : public UItemAbilityManagerBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void EquipItem(const FGameplayTag InItemTag);

	UFUNCTION(BlueprintCallable)
	void UnequipItem();

	virtual AActor* GetSpawnedItem() const override;
	
	UFUNCTION(BlueprintCallable)
	USigilPlayerSpawnedItemInstance* GetPlayerWeaponInstance() const {return CurrentActiveItem;}

	template<typename T>
	T* GetEquippedItemInstance() const
	{
		return Cast<T>(CurrentActiveItem);
	}

	virtual void CreateItemInstance(USigilItemSpecBase* InItemSpec) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USigilPlayerSpawnedItemInstance> CurrentActiveItem;

	UPROPERTY()
	TObjectPtr<ASigilPlayerCharacter> SigilPlayerCharacter;
	

};
