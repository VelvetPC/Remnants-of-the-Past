// remnants of the past.All Rights Reserved.


#include "UI/Class_UserWidget.h"
#include "Components/Class_WeaponComponent.h"
#include "Components/Class_HealthComponent.h"
#include "H_Utils.h"

float UClass_UserWidget::GetHealthPercent() const
{
	const auto HealthComponent = H_Utils::GetBTHPlayerComponent<UClass_HealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UClass_UserWidget::IsPlayerAlive() const
{
	const auto HealthComponent = H_Utils::GetBTHPlayerComponent<UClass_HealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UClass_UserWidget::IsPlayerSpectacing() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UClass_UserWidget::GetWeaponUIData(FWeaponData& UIData) const
{
	const auto WeaponComponent = H_Utils::GetBTHPlayerComponent<UClass_WeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UClass_UserWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = H_Utils::GetBTHPlayerComponent<UClass_WeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool UClass_UserWidget::Initialize()
{
	const auto HealthComponent = H_Utils::GetBTHPlayerComponent<UClass_HealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UClass_UserWidget::OnHealthChanged);
	}

	return Super::Initialize();
}

void UClass_UserWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
}

