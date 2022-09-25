// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Class_BaseWeapon.h"
#include "Class_LauncherWeapon.generated.h"

class AClass_Projectile;
class USoundCue;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_LauncherWeapon : public AClass_BaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashine")
		TSubclassOf<AClass_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* NoAmmoSound;


	virtual void MakeShot();
	
};
