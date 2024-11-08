#pragma once

#include "CoreMinimal.h"
#include "SmartGames/ANN/SG_Neuron.h"

#include "SG_SimpleNeuron.generated.h"

// SimpleNeuron
UCLASS()
class USG_SimpleNeuron : public USG_Neuron
{
	GENERATED_BODY()

public:
	virtual float Evaluate() override;
};