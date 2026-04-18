// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SigilBaseGameState.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(SigilGameState, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameReadyEvent);

UCLASS()
class SIGIL_API ASigilBaseGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	int32 AssetsToLoad = 0;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGameReady = false;

	UFUNCTION()
	void SetGameReady();
	
	UFUNCTION()
	void RegisterLoad();

	UFUNCTION()
	void MarkLoadComplete();
	
	UFUNCTION(BlueprintCallable, Category ="GameState|Loading")
	bool AreAllAssetsLoaded() const { return AssetsToLoad <= 0; }

	UFUNCTION(BlueprintCallable, Category="GameState|Loading")
	int32 GetPendingAssetsToLoad() const { return AssetsToLoad; }

	UPROPERTY(BlueprintAssignable, Category = "GameState|Loading")
	FOnGameReadyEvent GameReadyEvent;

};
