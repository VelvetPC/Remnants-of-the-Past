// remnants of the past.All Rights Reserved.


#include "AI/Services/Class_FindEnemyService.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "H_Utils.h"
#include "AI/Class_PerceptionComponent.h"

UClass_FindEnemyService::UClass_FindEnemyService()
{
	{
		NodeName = "Find Enemy";
	}
}

void UClass_FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = H_Utils::GetBTHPlayerComponent<UClass_PerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}