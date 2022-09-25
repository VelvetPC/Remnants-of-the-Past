// remnants of the past.All Rights Reserved.


#include "Development/Class_SoundBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

AClass_SoundBox::AClass_SoundBox()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->SetupAttachment(GetRootComponent());
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(CapsuleComponent);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}


void AClass_SoundBox::BeginPlay()
{
	Super::BeginPlay();
}

void AClass_SoundBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	Destroy();
}



