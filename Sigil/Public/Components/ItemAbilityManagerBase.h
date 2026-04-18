// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ItemAbilityManagerBase.generated.h"


class USigilAbilitySystemComponent;
class USigilItemInstanceBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIGIL_API UItemAbilityManagerBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemAbilityManagerBase();

	UFUNCTION(BlueprintCallable)
	virtual void CreateItemInstance(USigilItemSpecBase* InItemSpec) {};

	UFUNCTION(BlueprintCallable)
	virtual AActor* GetSpawnedItem() const {return nullptr;}

	UFUNCTION(BlueprintCallable)
	void SetCollisionForActiveItem(const bool bEnabled);
	
	UFUNCTION(BlueprintCallable)
	USigilItemInstanceBase* GetItemInstance(const FGameplayTag InItemTag) const;
	
	template<typename T>
	T* GetTypedItemInstance(const FGameplayTag InItemTag) const
	{
		if (USigilItemInstanceBase* Base = GetItemInstance(InItemTag))
		{
			return Cast<T>(Base);
		}
		return nullptr;
	}

	template<typename T>
	T* GetSpawnedItemAs() const
	{
	    return Cast<T>(GetSpawnedItem());
	}
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<class ASigilCharacterBase> SigilCharacter;

	UPROPERTY()
	TObjectPtr<USigilAbilitySystemComponent> SigilAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwnerSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag CurrentItemTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, TObjectPtr<USigilItemInstanceBase>> CurrentItemMap;
	
};
