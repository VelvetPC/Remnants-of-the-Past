// remnants of the past.All Rights Reserved.


#include "Development/Class_Damage.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AClass_Damage::AClass_Damage()
{
 	
	PrimaryActorTick.bCanEverTick = true;


	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

}


void AClass_Damage::BeginPlay()
{
	Super::BeginPlay();
	
}


void AClass_Damage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);

}

