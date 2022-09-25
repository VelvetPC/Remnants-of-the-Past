// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "Class_PerceptionComponent.generated.h"

UCLASS()
class REMNANTSOFTHEPAST_API UClass_PerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetClosesEnemy();


};
