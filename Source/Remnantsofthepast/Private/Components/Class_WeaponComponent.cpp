// remnants of the past.All Rights Reserved.


#include "Components/Class_WeaponComponent.h"
#include "Weapons/Class_BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/Class_EquipFinishedAnimNotify.h"
#include "Animations/Class_ReloadFinishedNotify.h"
#include "Animations/Class_WPN_ReloadNotify.h"
#include "Anim_Utils.h"
#include "Actors/Class_Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

constexpr static int32 MashineNum = 2;


UClass_WeaponComponent::UClass_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UClass_WeaponComponent::StartFire()
{
	if (!CantFire()) return;
	CurrentMashine->StartFire();
	

}

void UClass_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//checkf(MashineData.Num() == MashineNum, TEXT("2 mashines"), MashineNum);
	CurrentMashineIndex = 0;
	InitAnimations();
	SpawnMashines();
	EquipMashine(CurrentMashineIndex);

}

void UClass_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentMashine = nullptr;
	for (auto Mashine : Mashines)
	{
		Mashine->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Mashine->Destroy();

		UE_LOG(LogWeapon, Display, TEXT("super"));
	}

	Mashines.Empty();

	Super::EndPlay(EndPlayReason);

}

void UClass_WeaponComponent::SpawnMashines()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OnMashineData : MashineData)
	{
		auto Mashine = GetWorld()->SpawnActor<AClass_BaseWeapon>(OnMashineData.WeaponClass);
		if (!Mashine) continue;

		Mashine->OnClipEmpty.AddUObject(this, &UClass_WeaponComponent::OnEmptyClip);
		Mashine->SetOwner(Character);
		Mashines.Add(Mashine);

		AttachMashineToSocket(Mashine, Character->GetMesh(), ArmorySocketName);
	}
}

void UClass_WeaponComponent::EquipMashine(int32 MashineIndex)
{

	PlayAnimMontage(EquipAnimMontage);

	if (MashineIndex < 0 || MashineIndex >= Mashines.Num())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentMashine)
	{
		CurrentMashine->Zoom(false);
		CurrentMashine->StopFire();
		AttachMashineToSocket(CurrentMashine, Character->GetMesh(), ArmorySocketName);
	}

	CurrentMashine = Mashines[MashineIndex];
	//CurrentReloadAnimMontage = MashineData[MashineIndex].ReloadAnimMontage;
	const auto CurrentMashineData = MashineData.FindByPredicate([&](const FMashineData& Data)
	{ return Data.WeaponClass == CurrentMashine->GetClass();

	});

	CurrentReloadAnimMontage = CurrentMashineData ? CurrentMashineData->ReloadAnimMontage : nullptr;

	AttachMashineToSocket(CurrentMashine, Character->GetMesh(), EquipSocketName);
	EquipAnimInProgress = false;
	
}

void UClass_WeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UClass_WeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = Autils::FindNotifyByClass<UClass_EquipFinishedAnimNotify>(EquipAnimMontage);

	if (EquipFinishedNotify)
	{
	  EquipFinishedNotify->OnNotifired.AddUObject(this, &UClass_WeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeapon, Error, TEXT("Not notify"));
		//checkNoEntry();
	}


	for (auto OneMashineData : MashineData)
	{
		auto ReloadFinishedNotify = Autils::FindNotifyByClass<UClass_ReloadFinishedNotify>(OneMashineData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeapon, Error, TEXT("Not notify"));
			//checkNoEntry();
		}

	ReloadFinishedNotify->OnNotifired.AddUObject(this, &UClass_WeaponComponent::OnReloadFinished);

	}

}

bool UClass_WeaponComponent::CantFire() const
{
	return CurrentMashine && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UClass_WeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

void UClass_WeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;

	EquipAnimInProgress = false;

}

void UClass_WeaponComponent::AttachMashineToSocket(AClass_BaseWeapon* Mashine, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Mashine || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Mashine->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UClass_WeaponComponent::StopFire()
{
	if (!CurrentMashine) return;
	CurrentMashine->StopFire();
	FireAnimInProgress = false;
}

void UClass_WeaponComponent::NextMashine()
{
	if (!CanEquip()) return;
	CurrentMashineIndex = (CurrentMashineIndex + 1) % Mashines.Num();
	EquipMashine(CurrentMashineIndex);

}

void UClass_WeaponComponent::Reload()
{
	ChangeClip();

	CurrentMashine-> AClass_BaseWeapon::PlayAnimReload();

}

bool UClass_WeaponComponent::GetWeaponUIData(FWeaponData& UIData) const
{
	{
		if (CurrentMashine)
		{
			UIData = CurrentMashine->GetUIData();
			return true;
		}
		return false;
	}
}

bool UClass_WeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	{
		if (CurrentMashine)
		{
			AmmoData = CurrentMashine->GetAmmoData();
			return true;
		}
		return false;
	}
}

void UClass_WeaponComponent::Zoom(bool Enabled)
{
	if (CurrentMashine)
	{
		CurrentMashine->Zoom(Enabled);
		PlayAnimMontage(WPNZoomAnim);
	}
}

void UClass_WeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;
	UE_LOG(LogWeapon, Error, TEXT("03"));
	ReloadAnimInProgress = false;
}


bool UClass_WeaponComponent::CanReload() const
{
	return CurrentMashine && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentMashine->CanReload();
}

void UClass_WeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void UClass_WeaponComponent::ChangeClip()
{
	if (!CanReload()) return;
	CurrentMashine->StopFire();
	CurrentMashine->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}















