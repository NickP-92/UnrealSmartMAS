#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "SG_AnimInstance.generated.h"

// AnimInstance
UCLASS()
class USG_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsMoving { false };
};