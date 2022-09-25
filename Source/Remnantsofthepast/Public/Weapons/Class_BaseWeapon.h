// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_CoreTypes.h"
#include "Class_BaseWeapon.generated.h"


class USkeletalMeshComponent;
class USphereComponent;
class USoundCue;
class UNiagaraSystem;
class UNiagaraComponent;


UCLASS()
class REMNANTSOFTHEPAST_API AClass_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AClass_BaseWeapon();

	FOnClipEmptySignature OnClipEmpty;
	virtual void StartFire();
	virtual void StopFire();
	virtual void PlayAnimReload();

	void ChangeClip();
	bool CanReload() const;
	virtual void Zoom(bool Enabled) {};
	FWeaponData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo;}

	bool IsAmmoEmpty() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FName MuzzleSocketName = "MazzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		FAmmoData DefaultAmmo {15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FWeaponData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
		UAnimationAsset* WeaponReloadAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
		UAnimationAsset* WeaponFireAnim;

	

	virtual void BeginPlay() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeShot();
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecraeseAmmo();
	
	bool IsClickEmpty() const;
	void LogAmmo();
	void FireAnim();
	

	

	UNiagaraComponent* SpawnMuzzleFX();

private:
	FAmmoData CurrentAmmo;

	

};
