// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "H_CoreTypes.h"
#include "Class_UserWidget.generated.h"


UCLASS()
class REMNANTSOFTHEPAST_API UClass_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsPlayerSpectacing() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetWeaponUIData(FWeaponData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetWeaponAmmoData(FAmmoData& AmmoData) const;



	virtual bool Initialize() override;

private:

	void OnHealthChanged(float Health, float HealhtDelta);
};
