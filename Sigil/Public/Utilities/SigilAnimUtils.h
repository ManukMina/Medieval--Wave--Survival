// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SigilAnimUtils.generated.h"


UENUM(BlueprintType)
enum class ECardinalDirections : uint8
{

	Forward,
	Backward,
	Right,
	Left
	
};


UENUM()
enum class EMovementState : uint8
{
	Walking,
	Jogging
};


UCLASS()
class SIGIL_API USigilAnimUtils : public UObject
{
	GENERATED_BODY()

public:
	static float CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation);
};
