#include "SmartGames/ANN/SG_InputNeuron.h"

#include "SmartGames/ANN/SG_Connection.h"

void USG_InputNeuron::SetValue(float NewValue)
{
    Value = NewValue;
}

float USG_InputNeuron::Evaluate()
{
    return Value;
}
