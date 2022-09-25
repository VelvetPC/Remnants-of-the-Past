// remnants of the past.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_SoundBox.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class USoundCue;

UCLASS()
class REMNANTSOFTHEPAST_API AClass_SoundBox : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AClass_SoundBox();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* Sound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Static")
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Static")
		UStaticMeshComponent* StaticMesh;
	
	
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

};
