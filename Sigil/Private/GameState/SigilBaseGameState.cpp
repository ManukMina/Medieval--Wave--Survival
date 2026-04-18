// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "GameState/SigilBaseGameState.h"

DEFINE_LOG_CATEGORY(SigilGameState);


void ASigilBaseGameState::SetGameReady()
{
	if (bIsGameReady) return;
	bIsGameReady = true;
	GameReadyEvent.Broadcast();
}

void ASigilBaseGameState::RegisterLoad()
{
	++AssetsToLoad;
	UE_LOG(SigilGameState, Log, TEXT("Registered load. Pending assets: %d"), AssetsToLoad);
}

void ASigilBaseGameState::MarkLoadComplete()
{
	--AssetsToLoad;
	AssetsToLoad = FMath::Max(AssetsToLoad, 0); // Prevent negative count
	UE_LOG(SigilGameState, Log, TEXT("Marked load complete. Pending assets: %d"), AssetsToLoad);
	
}

