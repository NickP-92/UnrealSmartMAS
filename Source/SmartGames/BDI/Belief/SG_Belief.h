#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SmartGames/BDI/Belief/SG_BeliefType.h"

#include "SG_Belief.generated.h"

// Belief
USTRUCT(BlueprintType)
struct FSG_Belief
{
	GENERATED_BODY()

public:
	float Evaluate() const;

	UPROPERTY(EditDefaultsOnly)
	ESG_BeliefType Type { ESG_BeliefType::NoType };

	UPROPERTY(EditDefaultsOnly)
	float Value { 0.0f };

	UPROPERTY(EditDefaultsOnly)
	FFloatRange Range { 0.0f, 1.0f };
};