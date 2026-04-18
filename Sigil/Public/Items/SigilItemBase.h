// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SigilItemBase.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class SIGIL_API ASigilItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASigilItemBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Item|Mesh")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetItemCollision, Category="Sigil|Item|Collision")
	TObjectPtr<UBoxComponent> ItemCollision;

public:
	UFUNCTION(BlueprintGetter)
	UBoxComponent* GetItemCollision() const {return ItemCollision;};
	
	UFUNCTION(BlueprintCallable)
	void SetItemCollision(const bool bEnabled) const;
};
