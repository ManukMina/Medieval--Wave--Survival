// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Animation/SigilPlayerAnimInstance.h"
#include "Characters/SigilCharacterBase.h"
#include "Characters/SigilPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utilities/SigilAnimUtils.h"


void USigilPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (!IsValid(OwningPlayer) || !MovementComponent) return;

	SigilPlayerCharacter = Cast<ASigilPlayerCharacter>(OwningPlayer);
	WorldLocation = OwningPlayer->GetActorLocation(); 
	CardinalDeadzone = 10.0f;
	bIsFirstUpdate = true;
	
}

void USigilPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(OwningPlayer)) return;
	
	WorldRotation = OwningPlayer->GetActorRotation();
	WorldAcceleration2D = MovementComponent->GetCurrentAcceleration() * FVector(1.0f, 1.0f, 0.0f);

	//Take the acceleration in world space and express it in the character's local space (i.e., forward/right axes).
	LocalAcceleration2D = WorldRotation.UnrotateVector(WorldAcceleration2D);
	bHasAcceleration = LocalAcceleration2D.SizeSquared2D()>0.0f;
	
	// Update Velocity Data
	WorldVelocity2D = WorldVelocity * FVector(1.0f, 1.0f, 0.0f);
	bWasMovingLastUpdate = !WorldVelocity2D.IsZero();
	VelocityDirectionAngle = USigilAnimUtils::CalculateDirection(WorldVelocity2D, WorldRotation);

	// Cardinal Direction From Angle
	VelocityDirection = CalculateDirectionFromAngle(CardinalDeadzone, bWasMovingLastUpdate);

	MovementState = SigilPlayerCharacter->GetMovementState();
	
	DisplacementLastUpdate = (OwningPlayer->GetActorLocation() - WorldLocation).Size2D();
	DisplacementSpeed = (DisplacementLastUpdate != 0.0f) ? (DisplacementLastUpdate / DeltaSeconds) : 0.0f;
	WorldLocation =  OwningPlayer->GetActorLocation();

	if (bIsFirstUpdate)
	{
		DisplacementLastUpdate = 0.0f;
		DisplacementSpeed = 0.0f;
	}
	
	bIsFirstUpdate = false;

}

ECardinalDirections USigilPlayerAnimInstance::CalculateDirectionFromAngle(const float InDeadZone, const bool bUseCurrentDirection) const
{

	const float AbsAngle = FMath::Abs(VelocityDirectionAngle);
	float FwdDeadzone = InDeadZone;
	float BwdDeadzone = InDeadZone;

	if(bUseCurrentDirection)
	{
		if(VelocityDirection == ECardinalDirections::Forward) {FwdDeadzone *= 1.5f;}
		if(VelocityDirection == ECardinalDirections::Backward) {BwdDeadzone *= 1.5f;}
	}
	
	if(AbsAngle <= 45.0f + FwdDeadzone) {return ECardinalDirections::Forward;}
	if(AbsAngle <= 135.0f - BwdDeadzone) {return ECardinalDirections::Backward;}
	if(VelocityDirectionAngle > 0.0f) {return ECardinalDirections::Right;}

	return ECardinalDirections::Left;
}

