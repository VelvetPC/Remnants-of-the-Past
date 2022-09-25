// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Class_Task_NextLocation.generated.h"


UCLASS()
class REMNANTSOFTHEPAST_API UClass_Task_NextLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UClass_Task_NextLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai")
	FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai")
		bool SelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai")
		FBlackboardKeySelector CenterKey;


};


