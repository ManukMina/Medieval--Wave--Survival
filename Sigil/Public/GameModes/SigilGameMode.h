// Copyright � 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SigilGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API ASigilGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> LoadingScreenWidgetClass;
	
	virtual void BeginPlay() override;
	void CheckIfGameReady();
	void TriggerGameReady();
	
protected:
	UPROPERTY()
	FTimerHandle LoadCheckTimer;

	UPROPERTY()
	FTimerHandle PostLoadTimer;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> ActiveLoadingScreen = nullptr;
};
