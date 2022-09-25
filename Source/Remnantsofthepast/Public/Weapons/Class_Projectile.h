// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UClass_VFXrComponent;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AClass_Projectile();

	void SetShotDirection(const FVector Direction) { ShotDirection = Direction; }



protected:
	UPROPERTY(VisibleAnywhere, Category = "Mashine")
		USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mashine")
		UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashine")
		float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashine")
		float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashine")
		bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mashine")
		float LifeSeconds = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "vfx")
		UClass_VFXrComponent* VFXComponent;

	virtual void BeginPlay() override;

private:

	FVector ShotDirection;

	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController()const;


};
