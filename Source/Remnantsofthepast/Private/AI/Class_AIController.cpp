// remnants of the past.All Rights Reserved.


#include "AI/Class_AIController.h"
#include "Actors/Class_AICharacter.h"
#include "AI/Class_PerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AClass_AIController::AClass_AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UClass_PerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void AClass_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AClass_AIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

void AClass_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto AiCharacter = Cast<AClass_AICharacter>(InPawn))
	{
		RunBehaviorTree(AiCharacter->BehaviorTreeAsset);
	}


}
