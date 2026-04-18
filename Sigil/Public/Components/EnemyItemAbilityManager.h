// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemAbilityManagerBase.h"
#include "Items/InstanceObjects/SigilEnemyItemInstanceBase.h"
#include "EnemyItemAbilityManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIGIL_API UEnemyItemAbilityManager : public UItemAbilityManagerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USigilEnemyItemInstanceBase> CurrentActiveItem;	
	
	virtual void CreateItemInstance(USigilItemSpecBase* InItemSpec) override;

	virtual AActor* GetSpawnedItem() const override;
};
