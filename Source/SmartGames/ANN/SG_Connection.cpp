#include "SmartGames/ANN/SG_Connection.h"

#include "SmartGames/ANN/SG_Neuron.h"

void USG_Connection::Setup(USG_Neuron* InInputNeuron, USG_Neuron* InOutputNeuron)
{
    InputNeuron = InInputNeuron;
    OutputNeuron = InOutputNeuron;
    SetWeight(FMath::FRand());
}

float USG_Connection::Evaluate() const
{
    return InputNeuron ? (InputNeuron->Evaluate() * Weight) : 0.0f;
}

float USG_Connection::GetWeight() const
{
    return Weight;
}

void USG_Connection::SetWeight(float InWeight)
{
    Weight = InWeight;
}
