#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SmartGames/BDI/Belief/SG_BeliefType.h"
#include "SmartGames/Utils/SG_ComparisonOperator.h"

#include "SG_Desire.generated.h"

// Desire
USTRUCT(BlueprintType)
struct FSG_Desire
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	ESG_BeliefType BeliefType;

	UPROPERTY(EditDefaultsOnly)
	float UnfulfilledValue { 0.0f };

	UPROPERTY(EditDefaultsOnly)
	float FulfilledValue{ 0.0f };
};