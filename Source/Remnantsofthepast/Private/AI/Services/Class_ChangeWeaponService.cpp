// remnants of the past.All Rights Reserved.


#include "AI/Services/Class_ChangeWeaponService.h"
#include "Components/Class_WeaponComponent.h"
#include "AIController.h"
#include "H_Utils.h"

UClass_ChangeWeaponService::UClass_ChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UClass_ChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (const auto Controller = OwnerComp.GetAIOwner())
    {
        const auto WeaponComponent = H_Utils::GetBTHPlayerComponent<UClass_WeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability) // random
        {
            WeaponComponent->NextMashine();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

