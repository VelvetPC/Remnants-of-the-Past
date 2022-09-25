// remnants of the past.All Rights Reserved.


#include "Components/Class_AIWeaponComponent.h"
#include "Weapons/Class_BaseWeapon.h"

void UClass_AIWeaponComponent::StartFire()
{

    if(!CantFire()) return;

    if (CurrentMashine->IsAmmoEmpty())
    {
        NextMashine();
    }
    else
    {
        CurrentMashine->StartFire();
    }
}

void UClass_AIWeaponComponent::NextMashine()
{
    if (!CanEquip()) return;

    int32 NextIndex = (CurrentMashineIndex + 1) % Mashines.Num();
    while (NextIndex != CurrentMashineIndex)
    {
        if (!Mashines[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex + 1) % Mashines.Num();
    }

    if (CurrentMashineIndex != NextIndex)
    {
        CurrentMashineIndex = NextIndex;
        EquipMashine(CurrentMashineIndex);
    }
}
