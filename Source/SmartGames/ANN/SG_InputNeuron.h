#pragma once

#include "CoreMinimal.h"
#include "SmartGames/ANN/SG_Neuron.h"

#include "SG_InputNeuron.generated.h"

// InputNeuron
UCLASS()
class USG_InputNeuron : public USG_Neuron
{
	GENERATED_BODY()

public:
	void SetValue(float NewValue);

	virtual float Evaluate() override;

protected:
	float Value { 0.0f };
};