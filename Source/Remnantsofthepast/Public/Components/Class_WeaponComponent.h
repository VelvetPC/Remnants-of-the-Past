// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "H_CoreTypes.h"
#include "Class_WeaponComponent.generated.h"

class AClass_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class REMNANTSOFTHEPAST_API UClass_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UClass_WeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextMashine();
	void Reload();

	bool GetWeaponUIData(FWeaponData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	
	void Zoom(bool Enabled);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashines")
		TArray<FMashineData> MashineData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashines")
		FName EquipSocketName = "ASocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashines")
		FName ArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashines")
		UAnimMontage* CurrentReloadMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* WPNZoomAnim;


	UPROPERTY()
		AClass_BaseWeapon* CurrentMashine = nullptr;

	UPROPERTY()
		TArray<AClass_BaseWeapon*> Mashines;

	int32 CurrentMashineIndex = 0;
	

	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	bool CantFire() const;
	bool CanEquip() const;
	void EquipMashine(int32 MashineIndex);

private:

	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage = nullptr;

	
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	bool FireAnimInProgress = false;


	void SpawnMashines();
	void AttachMashineToSocket(AClass_BaseWeapon* Mashine, USceneComponent* SceneComponent, const FName& SocketName);
	

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();

};
