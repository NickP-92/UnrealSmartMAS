#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "SG_SearchAlgorithm.generated.h"

class ASG_Agent;

// Search algorithm
UCLASS()
class USG_SearchAlgorithm : public UObject
{
	GENERATED_BODY()

public:
	virtual void Search(TArray<ASG_Agent*>& Population) const PURE_VIRTUAL(&USG_SearchAlgorithm::Search; return;);
};