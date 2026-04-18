// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "GameModes/SigilGameMode.h"
#include "Blueprint/UserWidget.h"
#include "GameState/SigilBaseGameState.h"


void ASigilGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(LoadCheckTimer, this, &ASigilGameMode::CheckIfGameReady, 0.05f, true);
	if (LoadingScreenWidgetClass)
	{
		ActiveLoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidgetClass);
		if (ActiveLoadingScreen)
		{
			ActiveLoadingScreen->AddToViewport();
		}
	}
}

void ASigilGameMode::CheckIfGameReady()
{
	if (ASigilBaseGameState* SigilGameStateBase = Cast<ASigilBaseGameState>(GameState))
	{
		if (SigilGameStateBase->AreAllAssetsLoaded())
		{
			GetWorld()->GetTimerManager().ClearTimer(LoadCheckTimer);
			
			//Allow things to "settle" before starting the game.
			GetWorld()->GetTimerManager().SetTimer(PostLoadTimer, this, &ASigilGameMode::TriggerGameReady, 4.0f, false);
		}
	}
}

void ASigilGameMode::TriggerGameReady()
{
	if (ASigilBaseGameState* SigilGameStateBase = GetGameState<ASigilBaseGameState>())
	SigilGameStateBase->SetGameReady();
	
	if (ActiveLoadingScreen)
	{
		ActiveLoadingScreen->RemoveFromParent();
		ActiveLoadingScreen = nullptr;
	}
} 