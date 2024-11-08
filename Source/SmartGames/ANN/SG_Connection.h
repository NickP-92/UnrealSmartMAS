#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "SG_Connection.generated.h"

class USG_Neuron;

// Connection
UCLASS()
class USG_Connection : public UObject
{
	GENERATED_BODY()

public:
	void Setup(USG_Neuron* InInputNeuron, USG_Neuron* InOutputNeuron);
	float Evaluate() const;

	float GetWeight() const;
	void SetWeight(float InWeight);

protected:
	UPROPERTY()
	USG_Neuron* InputNeuron{ nullptr };
	
	UPROPERTY()
	USG_Neuron* OutputNeuron { nullptr };

	float Weight { 0.0f };
};