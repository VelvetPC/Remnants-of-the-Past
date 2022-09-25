// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Class_Character.h"
#include "Class_AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_AICharacter : public AClass_Character
{
	GENERATED_BODY()

public:
	
	AClass_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:

	virtual void OnDeath() override;
	
};
