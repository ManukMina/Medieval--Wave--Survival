// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#include "SpawnEnemy.h"
#include "Engine/TargetPoint.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include  "Characters/SigilEnemyCharacter.h"
#include "Characters/SigilPlayerCharacter.h"

ASpawnEnemy::ASpawnEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnEnemy::HideAbilityUnlockedWidget()
{
	if (ActiveAbilityUnlockedWidget)
	{
		ActiveAbilityUnlockedWidget-> RemoveFromParent();
		ActiveAbilityUnlockedWidget = nullptr;
	}
}

void ASpawnEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (bStartFirstWaveOnBeginPlay)
	{
		StartWaveManager();
	}
}

void ASpawnEnemy::StartWaveManager()
{
	CurrentWaveIndex = -1;
	AliveEnemies = 0;
	SpawnedThisWave = 0;
	TotalToSpawnThisWave = 0;
	PendingEnemies.Empty();

	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorldTimerManager().ClearTimer(NextWaveTimerHandle);

	StartNextWave();
}

void ASpawnEnemy::StartNextWave()
{
	CurrentWaveIndex++;

	if (!Waves.IsValidIndex(CurrentWaveIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("WaveManager: no more waves to start.Victory"));
		HandleVictory();
		return;
	}

	SpawnedThisWave = 0;
	TotalToSpawnThisWave = 0;
	PendingEnemies.Empty();

	BuildPendingEnemiesForCurrentWave();
	TotalToSpawnThisWave = PendingEnemies.Num();

	UE_LOG(LogTemp, Warning, TEXT("WaveManager: starting wave %d, total enemies = %d"),
		CurrentWaveIndex + 1,
		TotalToSpawnThisWave);

	if (TotalToSpawnThisWave <= 0)
	{
		GetWorldTimerManager().SetTimer(
			NextWaveTimerHandle,
			this,
			&ASpawnEnemy::StartNextWave,
			TimeBetweenWaves,
			false
		);
		return;
	}

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawnEnemy::TrySpawnNextEnemy,
		SpawnInterval,
		true,
		0.0f
	);
}

void ASpawnEnemy::BuildPendingEnemiesForCurrentWave()
{
	if (!Waves.IsValidIndex(CurrentWaveIndex))
	{
		return;
	}

	const FWaveData& Wave = Waves[CurrentWaveIndex];

	for (const FWaveEnemyEntry& Entry : Wave.Enemies)
	{
		if (!Entry.EnemyClass || Entry.Count <= 0)
		{
			continue;
		}

		for (int32 i = 0; i < Entry.Count; i++)
		{
			PendingEnemies.Add(Entry.EnemyClass);
		}
	}
}

void ASpawnEnemy::TrySpawnNextEnemy()
{
	if (AliveEnemies >= MaxAliveEnemies)
	{
		return;
	}

	if (PendingEnemies.Num() <= 0)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

		if (IsCurrentWaveFinished())
		{
			GetWorldTimerManager().SetTimer(
				NextWaveTimerHandle,
				this,
				&ASpawnEnemy::StartNextWave,
				TimeBetweenWaves,
				false
			);
		}

		return;
	}

	if (SpawnPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("WaveManager: SpawnPoints array is empty."));
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	const int32 RandomSpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
	ATargetPoint* SpawnPoint = SpawnPoints[RandomSpawnPointIndex];

	if (!SpawnPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("WaveManager: SpawnPoint is null."));
		return;
	}

	TSubclassOf<AActor> EnemyClass = PendingEnemies[0];
	PendingEnemies.RemoveAt(0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(
		EnemyClass,
		SpawnPoint->GetActorTransform(),
		SpawnParams
	);
	ASigilEnemyCharacter* SpawnedEnemyCharacter = Cast<ASigilEnemyCharacter>(SpawnedEnemy);
	if (SpawnedEnemyCharacter)
	{
		SpawnedEnemyCharacter->SpawnEnemyManager = this;
	}
	
	if (SpawnedEnemy)
	{
		AliveEnemies++;
		SpawnedThisWave++;

		UE_LOG(LogTemp, Warning, TEXT("WaveManager: spawned enemy. AliveEnemies = %d, SpawnedThisWave = %d"),
			AliveEnemies,
			SpawnedThisWave);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaveManager: failed to spawn enemy."));
	}

	if (PendingEnemies.Num() <= 0)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

		if (IsCurrentWaveFinished())
		{
			GetWorldTimerManager().SetTimer(
				NextWaveTimerHandle,
				this,
				&ASpawnEnemy::StartNextWave,
				TimeBetweenWaves,
				false
			);
		}
	}
}

void ASpawnEnemy::NotifyEnemyDied(AActor* DeadEnemy)
{
	if (AliveEnemies > 0)
	{
		AliveEnemies--;
	}

	UE_LOG(LogTemp, Warning, TEXT("WaveManager: enemy died. AliveEnemies = %d"), AliveEnemies);

	if (IsCurrentWaveFinished())
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

		const int32 NextWaveIndex = CurrentWaveIndex + 1;
		if (!Waves.IsValidIndex(NextWaveIndex))
		{
			UE_LOG(LogTemp, Warning, TEXT("WaveManager: last enemy died, no more waves. Victory."));
			HandleVictory();
			return;
		}
		
		if (CurrentWaveIndex ==3)
		{
			ASigilPlayerCharacter* Player = Cast<ASigilPlayerCharacter>(GetWorld() -> GetFirstPlayerController() ->GetPawn());
			if (Player)
			{
				Player->UnlockHeavyAttack();
			}
			if (AbilityUnlockedWidgetClass)
			{
				ActiveAbilityUnlockedWidget= CreateWidget<UUserWidget>(GetWorld(), AbilityUnlockedWidgetClass);
				if (ActiveAbilityUnlockedWidget)
				{
					ActiveAbilityUnlockedWidget->AddToViewport();

					GetWorldTimerManager().SetTimer(AbilityUnlockedWidgetTimer,
						this,
						&ASpawnEnemy::HideAbilityUnlockedWidget,4.0f, false);
				}
			}
		
		}
		GetWorldTimerManager().SetTimer(
			NextWaveTimerHandle,
			this,
			&ASpawnEnemy::StartNextWave,
			TimeBetweenWaves,
			false
		);
	}
}
	bool ASpawnEnemy::IsCurrentWaveFinished() const
	{
		return PendingEnemies.Num() == 0
			&& AliveEnemies == 0
			&& SpawnedThisWave >= TotalToSpawnThisWave;
	}
