// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/SigilItemBase.h"

#include "Components/BoxComponent.h"


// Sets default values
ASigilItemBase::ASigilItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	ItemCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollision"));
	ItemCollision->SetupAttachment(RootComponent);
	ItemCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemCollision->SetBoxExtent(FVector(15.0f, 15.0f, 15.0f));
	
}

void ASigilItemBase::SetItemCollision(const bool bEnabled) const 
{
	ItemCollision->SetCollisionEnabled(bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}



