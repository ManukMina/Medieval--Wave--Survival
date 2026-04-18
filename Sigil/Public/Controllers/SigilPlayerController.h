// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "SigilPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API ASigilPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ASigilPlayerController();
	virtual void BeginPlay() override;

	//~ Begin IGenericTeamAgentInterface Interface
	virtual FGenericTeamId GetGenericTeamId() const override { return PlayerTeamID; }
	//~ End IGenericTeamAgentInterface Interface


protected:
	UPROPERTY()
	FGenericTeamId PlayerTeamID;

	UFUNCTION()
	void HandleGameReady();
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void HandleQuitGame();
	
};
