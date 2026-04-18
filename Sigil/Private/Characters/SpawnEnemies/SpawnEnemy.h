// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemy.generated.h"

class ATargetPoint;

USTRUCT(BlueprintType)
struct FWaveEnemyEntry
{
	GENERATED_BODY()

	// Enemy class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<AActor> EnemyClass;

	// How many enemies of this class should be spawned in this wave
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 Count = 0;
};

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	// Enemy list for this wave
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<FWaveEnemyEntry> Enemies;
};

UCLASS()
class SIGIL_API ASpawnEnemy : public AActor
{
	GENERATED_BODY()

public:
	ASpawnEnemy();

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Manager")
	void HandleVictory();
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> AbilityUnlockedWidgetClass;

	UPROPERTY()
    TObjectPtr<UUserWidget> ActiveAbilityUnlockedWidget = nullptr;

	 FTimerHandle AbilityUnlockedWidgetTimer;

	void HideAbilityUnlockedWidget();
	
protected:
	virtual void BeginPlay() override;

	// All waves. You will fill this in the Blueprint child.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	TArray<FWaveData> Waves;

	// Spawn points placed in the level
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	TArray<ATargetPoint*> SpawnPoints;

	// Maximum number of alive enemies at the same time
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	int32 MaxAliveEnemies = 10;

	// Delay between individual enemy spawns inside the same wave
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	float SpawnInterval = 2.0f;

	// Delay before the next wave starts after the current wave is finished
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	float TimeBetweenWaves = 30.0f;

	// Start automatically on BeginPlay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	bool bStartFirstWaveOnBeginPlay = true;

	// Current wave index (0-based)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	int32 CurrentWaveIndex = -1;

	// Number of currently alive enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	int32 AliveEnemies = 0;

	// Number of enemies already spawned in the current wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	int32 SpawnedThisWave = 0;

	// Total number of enemies that must be spawned in the current wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	int32 TotalToSpawnThisWave = 0;

	// Internal spawn queue for the current wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave Manager")
	TArray<TSubclassOf<AActor>> PendingEnemies;

	

	FTimerHandle SpawnTimerHandle;
	FTimerHandle NextWaveTimerHandle;

	// Starts the next wave
	void StartNextWave();

	// Builds the internal pending spawn list for the current wave
	void BuildPendingEnemiesForCurrentWave();

	// Tries to spawn one enemy if conditions allow it
	void TrySpawnNextEnemy();

	// Checks if the current wave is completely finished
	bool IsCurrentWaveFinished() const;

public:
	// Call this manually if auto-start is disabled
	UFUNCTION(BlueprintCallable, Category = "Wave Manager")
	void StartWaveManager();

	// Call this from enemy death logic
	UFUNCTION(BlueprintCallable, Category = "Wave Manager")
	void NotifyEnemyDied(AActor* DeadEnemy);

	// Debug helper
	UFUNCTION(BlueprintPure, Category = "Wave Manager")
	int32 GetCurrentWaveNumber() const
	{
		return CurrentWaveIndex + 1;
	}
};