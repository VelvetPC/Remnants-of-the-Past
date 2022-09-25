// remnants of the past.All Rights Reserved.


#include "AI/Services/Class_FireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "H_Utils.h"
#include "Components/Class_WeaponComponent.h"


UClass_FireService::UClass_FireService()
{
	NodeName = "Fire";
}

void UClass_FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WComponent = H_Utils::GetBTHPlayerComponent<UClass_WeaponComponent>(Controller->GetPawn());
		if (WComponent)
		{
			HasAim ? WComponent->StartFire() : WComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

