#include "SmartGames/Animation/SG_AnimInstance.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

void USG_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwningActor()))
	{
		const FVector Velocity = Owner->GetVelocity();
		bIsMoving = FMath::IsNearlyZero(Velocity.Z)
			&& (!FMath::IsNearlyZero(Velocity.X) || !FMath::IsNearlyZero(Velocity.Y));
	}
}
