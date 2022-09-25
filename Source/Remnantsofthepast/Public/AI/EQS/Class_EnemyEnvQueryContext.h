// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "Class_EnemyEnvQueryContext.generated.h"

UCLASS()
class REMNANTSOFTHEPAST_API UClass_EnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        FName EnemyActorKeyName = "EnemyActor";
};
