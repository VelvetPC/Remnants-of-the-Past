// remnants of the past.All Rights Reserved.


#include "Components/Class_CharacterMovementComponent.h"
#include "Actors/Class_Character.h"

float UClass_CharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AClass_Character* Player = Cast<AClass_Character>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;

}