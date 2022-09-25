// remnants of the past.All Rights Reserved.


#include "AI/Class_PerceptionComponent.h"
#include "AI/Class_AIController.h"
#include "H_Utils.h"
#include "Components/Class_HealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UClass_PerceptionComponent::GetClosesEnemy()
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = H_Utils::GetBTHPlayerComponent<UClass_HealthComponent>(PercieveActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}
