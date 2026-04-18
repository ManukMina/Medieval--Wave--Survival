// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Controllers/SigilPlayerController.h"

#include "GameState/SigilBaseGameState.h"
#include "Kismet/KismetSystemLibrary.h"

ASigilPlayerController::ASigilPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

void ASigilPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	ASigilBaseGameState* SigilGameStateBase = GetWorld()->GetGameState<ASigilBaseGameState>();
	if (SigilGameStateBase)
	{
		if (!SigilGameStateBase->bIsGameReady)
		{
			DisableInput(this);
			SigilGameStateBase->GameReadyEvent.AddDynamic(this, &ASigilPlayerController::HandleGameReady);
		}
		
		else
		{
			HandleGameReady();
		}

	}
	
}

void ASigilPlayerController::HandleGameReady()
{
	EnableInput(this);
}

void ASigilPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent -> BindKey(EKeys::Escape, IE_Pressed, this, &ASigilPlayerController::HandleQuitGame);
	}
}
void ASigilPlayerController::HandleQuitGame()
{
	UKismetSystemLibrary:: QuitGame(this, this, EQuitPreference::Quit, false);
}
