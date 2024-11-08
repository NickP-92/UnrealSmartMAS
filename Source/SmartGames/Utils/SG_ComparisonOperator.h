#pragma once

#include "CoreMinimal.h"

// ComparisonOperator
UENUM(BlueprintType)
enum class ESG_ComparisonOperator : uint8
{
	Equal,
	NotEqual,
	Greater,
	GreaterOrEqual,
	Less,
	LessOrEqual
};
