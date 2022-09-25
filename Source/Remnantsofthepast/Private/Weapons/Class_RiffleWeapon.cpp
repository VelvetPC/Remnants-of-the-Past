// remnants of the past.All Rights Reserved.


#include "Weapons/Class_RiffleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "VFX/Class_VFXrComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"

AClass_RiffleWeapon::AClass_RiffleWeapon()
{
	VFXComponent = CreateDefaultSubobject<UClass_VFXrComponent>("VFXComponent");
}

void AClass_RiffleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AClass_RiffleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void AClass_RiffleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

	SetFXActive(false);
}

void AClass_RiffleWeapon::BeginPlay()
{
	Super::BeginPlay();
	//check(VFXComponent);
}

void AClass_RiffleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
		{
			StopFire();
			return;
		}

	FVector TraceStart, TraceEnd;
		if (!GetTraceData(TraceStart, TraceEnd))
		{
			StopFire();
			return;
		}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;
		if (HitResult.bBlockingHit)
		{
			TraceFXEnd = HitResult.ImpactPoint;
			MakeDamage(HitResult);
			VFXComponent->PlayImpactFX(HitResult);
		}
	InitFX();
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, SkeletalMesh, MuzzleSocketName);
	DecraeseAmmo();
}

bool AClass_RiffleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AClass_RiffleWeapon::InitFX()
{
	if(!MuzzleFXComponent)
		{
			MuzzleFXComponent = SpawnMuzzleFX();
		}

	if (!FireAudioComponent)
	{
		//FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, SkeletalMesh, MuzzleSocketName);
	}

	SetFXActive(true);
}

void AClass_RiffleWeapon::SetFXActive(bool IsActive)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);
		MuzzleFXComponent->SetVisibility(IsActive, true);
	}

	if (FireAudioComponent)
	{
		//FireAudioComponent->SetPaused(!IsActive);
		IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
	}
}

void AClass_RiffleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);

}

void AClass_RiffleWeapon::SpawnTraceFX(const FVector& Tracestart, const FVector& TraceEnd)

{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, Tracestart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* AClass_RiffleWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void AClass_RiffleWeapon::Zoom(bool Enabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;

	if (Enabled)
	{
		DefaultCameraFov = Controller->PlayerCameraManager->GetFOVAngle();
	}

	Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoom : DefaultCameraFov);
}

