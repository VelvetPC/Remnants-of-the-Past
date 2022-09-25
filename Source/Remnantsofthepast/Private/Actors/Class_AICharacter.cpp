// remnants of the past.All Rights Reserved.


#include "Actors/Class_AICharacter.h"
#include "AI/Class_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Class_AIWeaponComponent.h"
#include "BrainComponent.h"

AClass_AICharacter::AClass_AICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UClass_AIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AClass_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);

	}
}

void AClass_AICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = Cast<AClass_AIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}
