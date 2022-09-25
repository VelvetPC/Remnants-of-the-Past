// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Class_FireService.generated.h"

UCLASS()
class REMNANTSOFTHEPAST_API UClass_FireService : public UBTService
{
	GENERATED_BODY()

public:

	UClass_FireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
