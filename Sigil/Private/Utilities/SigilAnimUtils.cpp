// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Utilities/SigilAnimUtils.h"

float USigilAnimUtils::CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation)
{

	if(!Velocity.IsNearlyZero())
	{
		const FVector ForwardVector = BaseRotation.Vector();
		const FVector RightVector = FRotationMatrix(BaseRotation).GetScaledAxis(EAxis::Y);
		const FVector NormalizedVelocity = Velocity.GetSafeNormal2D();

		float ForwardDeltaDegree = FMath::DegreesToRadians(FMath::Acos(FVector::DotProduct(ForwardVector, NormalizedVelocity)));

		if(FVector::DotProduct(RightVector, NormalizedVelocity) <0.0f )
		{
			ForwardDeltaDegree *= -1.f;
		}

		return ForwardDeltaDegree;
		
	}

	return 0.0f;
}
