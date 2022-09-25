// remnants of the past.All Rights Reserved.


#include "Weapons/Class_Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "VFX/Class_VFXrComponent.h"


AClass_Projectile::AClass_Projectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereComponent->bReturnMaterialOnMove = true;
	SetRootComponent(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	VFXComponent = CreateDefaultSubobject<UClass_VFXrComponent>("VFXComponent");
}


void AClass_Projectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent)
	check(VFXComponent)

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AClass_Projectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
	
}

void AClass_Projectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)

{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();
	//MAkeDamage
	UGameplayStatics::ApplyRadialDamage(GetWorld(),
		DamageAmount,
		GetActorLocation(),
		DamageRadius,
		UDamageType::StaticClass(),
		{ GetOwner() },
		this,
		GetController(),
		DoFullDamage);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
	VFXComponent->PlayImpactFX(Hit);
	Destroy();
}

AController* AClass_Projectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}



