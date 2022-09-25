// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Class_WeaponComponent.h"
#include "Class_AIWeaponComponent.generated.h"


UCLASS()
class REMNANTSOFTHEPAST_API UClass_AIWeaponComponent : public UClass_WeaponComponent
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;
	virtual void NextMashine() override;

};
