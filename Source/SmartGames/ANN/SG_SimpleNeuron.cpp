#include "SmartGames/ANN/SG_SimpleNeuron.h"

#include "SmartGames/ANN/SG_Connection.h"

float USG_SimpleNeuron::Evaluate()
{
	float NeuronValue = 0.0f;

	for (const USG_Connection* InputConnection : InputConnections)
	{
		NeuronValue += InputConnection->Evaluate();
	}

	return FMath::Max(0.0f, NeuronValue);
}
