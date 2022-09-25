// remnants of the past.All Rights Reserved.


#include "Animations/Class_AnimNotify.h"

void UClass_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifired.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation);
}
