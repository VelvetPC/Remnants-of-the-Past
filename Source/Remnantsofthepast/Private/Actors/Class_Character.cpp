// remnants of the past.All Rights Reserved.


#include "Actors/Class_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Class_HealthComponent.h"
#include "Components/InputComponent.h"
#include "Components/Class_CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Weapons/Class_BaseWeapon.h"
#include "Components/Class_WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "H_CoreTypes.h"




AClass_Character::AClass_Character(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UClass_CharacterMovementComponent>(AClass_Character::CharacterMovementComponentName))
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
	HealthComponent = CreateDefaultSubobject<UClass_HealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UClass_WeaponComponent>("WeaponComponent");

}

void AClass_Character::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AClass_Character::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AClass_Character::OnHealthChanged);
	LandedDelegate.AddDynamic(this, &AClass_Character::OnGroundLanded);
	
}

void AClass_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AClass_Character::MoveForward(float Amount)
{

	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
	if (Amount > 0.0f)
	{
		PlayCameraShakeMove();
	}

	
}

void AClass_Character::MoveRight(float Amount)
{
	
	AddMovementInput(GetActorRightVector(), Amount);
}

void AClass_Character::LoockUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AClass_Character::TurnArround(float Amount)
{
	AddControllerYawInput(Amount);
}

void AClass_Character::OnStartRunning()
{
	WantsToRun = true;
}

void AClass_Character::OnStopRunning()
{
	WantsToRun = false;
}

void AClass_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AClass_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AClass_Character::MoveRight);
	PlayerInputComponent->BindAxis("LoockUp", this, &AClass_Character::LoockUp);
	PlayerInputComponent->BindAxis("TurnArround", this, &AClass_Character::TurnArround);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AClass_Character::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AClass_Character::OnStopRunning);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AClass_Character::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UClass_WeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UClass_WeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextMashine", IE_Pressed, WeaponComponent, &UClass_WeaponComponent::NextMashine);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UClass_WeaponComponent::Reload);

	DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &UClass_WeaponComponent::Zoom, true);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &UClass_WeaponComponent::Zoom,false);


}

bool AClass_Character::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
	
}

float AClass_Character::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AClass_Character::OnDeath() 
{
	//PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpan);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);

	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
		
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AClass_Character::OnHealthChanged(float Health, float HealthDelta)
{
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), DamageSound, GetActorLocation());
}

void AClass_Character::PlayCameraShakeRun()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(RunCamera);
}

void AClass_Character::PlayCameraShakeMove()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(MovementCamera);
}

void AClass_Character::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelosityZ = -GetCharacterMovement()->Velocity.Z;
	//UE_LOG(CharacterLog, Display, TEXT("OnLanded: %f"), FallVelosityZ);

	if (FallVelosityZ < LandedDamageVelosity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelosity, LandedDamage, FallVelosityZ);
	//UE_LOG(CharacterLog, Display, TEXT("FinalDamage: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}


