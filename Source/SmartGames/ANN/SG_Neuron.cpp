#include "SmartGames/ANN/SG_Neuron.h"

void USG_Neuron::AddInputConnection(USG_Connection* Connection)
{
    InputConnections.Add(Connection);
}

void USG_Neuron::AddOutputConnection(USG_Connection* Connection)
{
    OutputConnections.Add(Connection);
}
