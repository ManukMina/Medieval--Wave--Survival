// Copyright © 2025 Hard Edge Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SigilAnimInstanceBase.h"
#include "SigilPlayerAnimInstance.generated.h"

class ASigilPlayerCharacter;
enum class EMovementState : uint8;
enum class ECardinalDirections : uint8;
class UCharacterMovementComponent;
class ASigilCharacterBase;
/**
 * 
 */
UCLASS()
class SIGIL_API USigilPlayerAnimInstance : public USigilAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(Transient)
    TObjectPtr<ASigilPlayerCharacter> SigilPlayerCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FVector WorldLocation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FRotator WorldRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FVector WorldAcceleration2D;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FVector LocalAcceleration2D;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	bool bHasAcceleration;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FVector WorldVelocity2D;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	bool bWasMovingLastUpdate;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	float VelocityDirectionAngle;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	float CardinalDeadzone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	bool bIsFirstUpdate;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	EMovementState MovementState;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	ECardinalDirections VelocityDirection;
	
	UFUNCTION()
	ECardinalDirections CalculateDirectionFromAngle(const float InDeadZone, const bool bUseCurrentDirection) const;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	float DisplacementLastUpdate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	float DisplacementSpeed;
	
	
};
