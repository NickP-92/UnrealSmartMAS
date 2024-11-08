#pragma once

#include "CoreMinimal.h"

// Belief Type
UENUM(BlueprintType)
enum class ESG_BeliefType : uint8
{
	NoType,
	Hunger,
	Thirst,
	Food,
	Drink
};
