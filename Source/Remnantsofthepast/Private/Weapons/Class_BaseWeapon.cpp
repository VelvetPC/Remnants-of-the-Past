// remnants of the past.All Rights Reserved.


#include "Weapons/Class_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Class_Character.h"

DEFINE_LOG_CATEGORY_STATIC(MashineLog, All, All);

AClass_BaseWeapon::AClass_BaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(SphereComponent);
	
}


void AClass_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	//check(SkeletalMesh);
	//checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count"));
	//checkf(DefaultAmmo.Clips > 0, TEXT("Clips count"));
	CurrentAmmo = DefaultAmmo;

}

void AClass_BaseWeapon::MakeShot()
{
 
}

void AClass_BaseWeapon::StartFire()
{
	//GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AClass_BaseWeapon::MakeShot, TimeBetweenShots, true);
	//MakeShot();
   

}

APlayerController* AClass_BaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool AClass_BaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto ACharacterW = Cast<ACharacter>(GetOwner());
	if (!ACharacterW) return false;

	if (ACharacterW->IsPlayerControlled())
	{
		const auto Controller = ACharacterW->GetController<APlayerController>();
		if (!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = SkeletalMesh->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector AClass_BaseWeapon::GetMuzzleWorldLocation() const
{
	return SkeletalMesh->GetSocketLocation(MuzzleSocketName);
}

bool AClass_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;

	const FVector ShootDirection = ViewRotation.Vector();

	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AClass_BaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	FireAnim();
	
}

void AClass_BaseWeapon::DecraeseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(MashineLog, Display, TEXT("____clip is empty______"));
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsClickEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool AClass_BaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClickEmpty();
}

bool AClass_BaseWeapon::IsClickEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void AClass_BaseWeapon::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(MashineLog, Display, TEXT("_____No clips______"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool AClass_BaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}


void AClass_BaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(MashineLog, Display, TEXT("%s"), *AmmoInfo);
}

void AClass_BaseWeapon::FireAnim()
{
	SkeletalMesh->PlayAnimation(WeaponFireAnim, false);
}

UNiagaraComponent* AClass_BaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,  //
		SkeletalMesh,                                                //
		MuzzleSocketName,                                          //
		FVector::ZeroVector,                                       //
		FRotator::ZeroRotator,                                     //
		EAttachLocation::SnapToTarget, true);
}

void AClass_BaseWeapon::StopFire()
{
	//GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AClass_BaseWeapon::PlayAnimReload()
{

	SkeletalMesh->PlayAnimation(WeaponReloadAnim,false);

}

