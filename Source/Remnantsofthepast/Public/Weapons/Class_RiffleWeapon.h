// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Class_BaseWeapon.h"
#include "Class_RiffleWeapon.generated.h"


class UClass_VFXrComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_RiffleWeapon : public AClass_BaseWeapon
{
	GENERATED_BODY()

public:

	AClass_RiffleWeapon();


	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void Zoom(bool Enabled) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float TimeBetweenShots = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UClass_VFXrComponent* VFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FString TraceTargetName = "TraceTarget";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float FOVZoom = 50.0f;

	virtual void BeginPlay() override;
	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
		UNiagaraComponent* MuzzleFXComponent;
	UPROPERTY()
		UAudioComponent* FireAudioComponent;


	AController* GetController() const;

	float DefaultCameraFov = 90.0f;
	void InitFX();
	void SetFXActive(bool IsActive);
	void MakeDamage(const FHitResult& HitResult);
	void SpawnTraceFX(const FVector& Tracestart, const FVector& TraceEnd);
};
	

