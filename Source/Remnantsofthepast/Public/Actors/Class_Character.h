// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Class_Character.generated.h"

class UCameraComponent;
class UClass_HealthComponent;
class UClass_WeaponComponent;
class USoundCue;
class UCameraShakeBase;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_Character : public ACharacter
{
	GENERATED_BODY()

public:
	
	AClass_Character(const FObjectInitializer& ObjInit);


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UClass_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		FVector2D LandedDamageVelosity = FVector2D(500.0f, 800.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		UClass_WeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* DeathSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* DamageSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		TSubclassOf<UCameraShakeBase> RunCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		TSubclassOf<UCameraShakeBase> MovementCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destroy")
		float LifeSpan = 5.0f;
	
	
	virtual void BeginPlay() override;
	virtual void OnDeath();
	

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LoockUp(float Amount);
	void TurnArround(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	bool WantsToRun = false;
	bool IsMovingForward = false;

	void OnHealthChanged(float Health, float HealthDelta);

	void PlayCameraShakeRun();
	void PlayCameraShakeMove();

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);
};
