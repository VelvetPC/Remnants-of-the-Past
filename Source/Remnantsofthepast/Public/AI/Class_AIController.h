// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Class_AIController.generated.h"

class UClass_PerceptionComponent;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AClass_AIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UClass_PerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "EnemyActor";


	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;


};
