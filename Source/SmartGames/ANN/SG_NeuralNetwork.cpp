#include "SmartGames/ANN/SG_NeuralNetwork.h"

#include "SmartGames/ANN/SG_Connection.h"
#include "SmartGames/ANN/SG_InputNeuron.h"
#include "SmartGames/ANN/SG_Neuron.h"
#include "SmartGames/ANN/SG_SimpleNeuron.h"

namespace USG_NeuralNetwork_Internal
{
	FSG_Genome GenerateGenome(int32 Size)
	{
		FSG_Genome Genome;
		Genome.Reserve(Size);

		for (int32 Index = 0; Index < Size; ++Index)
		{
			Genome.Add(FMath::FRand());
		}

		return Genome;
	}
}

USG_NeuralNetwork* USG_NeuralNetwork::CreateNeuralNetwork(int32 InputNum, int32 HiddenNum, int32 OutputNum)
{
	USG_NeuralNetwork* NeuralNetwork = NewObject<USG_NeuralNetwork>();
	NeuralNetwork->InputLayer = CreateLayer<USG_InputNeuron>(InputNum);
	NeuralNetwork->HiddenLayer = CreateLayer<USG_SimpleNeuron>(HiddenNum);
	NeuralNetwork->OutputLayer = CreateLayer<USG_SimpleNeuron>(OutputNum);
	ConnectLayers<USG_InputNeuron, USG_SimpleNeuron>(NeuralNetwork->InputLayer, NeuralNetwork->HiddenLayer, NeuralNetwork->InputToHiddenConnections);
	ConnectLayers<USG_SimpleNeuron, USG_SimpleNeuron>(NeuralNetwork->HiddenLayer, NeuralNetwork->OutputLayer, NeuralNetwork->HiddenToOutputConnections);
	NeuralNetwork->Genome = USG_NeuralNetwork_Internal::GenerateGenome(NeuralNetwork->InputToHiddenConnections.Num() + NeuralNetwork->HiddenToOutputConnections.Num());

	return NeuralNetwork;
}

template<class T>
TArray<T*> USG_NeuralNetwork::CreateLayer(int32 NeuronNum)
{
	TArray<T*> Layer;
	Layer.Reserve(NeuronNum);

	for (int32 Index = 0; Index < NeuronNum; ++Index)
	{
		Layer.Add(NewObject<T>());
	}
	
	return Layer;
}

template<class T, class U>
void USG_NeuralNetwork::ConnectLayers(const TArray<T*>& FirstLayer, const TArray<U*>& SecondLayer, TArray<USG_Connection*>& Connections)
{
	const int32 FirstLayerNum = FirstLayer.Num();
	const int32 SecondLayerNum = SecondLayer.Num();

	Connections.Empty();
	Connections.Reserve(FirstLayerNum * SecondLayerNum);

	for (int32 FirstIndex = 0; FirstIndex < FirstLayerNum; ++FirstIndex)
	{
		USG_Neuron* FirstNeuron = Cast<USG_Neuron>(FirstLayer[FirstIndex]);

		for (int32 SecondIndex = 0; SecondIndex < SecondLayerNum; ++SecondIndex)
		{
			USG_Neuron* SecondNeuron = Cast<USG_Neuron>(SecondLayer[SecondIndex]);

			USG_Connection* FirstToSecondConnection = NewObject<USG_Connection>();
			Connections.Add(FirstToSecondConnection);

			FirstToSecondConnection->Setup(FirstNeuron, SecondNeuron);
			FirstNeuron->AddOutputConnection(FirstToSecondConnection);
			SecondNeuron->AddInputConnection(FirstToSecondConnection);
		}
	}
}

TArray<bool> USG_NeuralNetwork::Run(const TArray<float>& Inputs)
{
	SetInputs(Inputs);
	UpdateWeights();

	TArray<float> EvaluatedOutputLayer;
	float TotalOutput = 0.0f;

	for (USG_Neuron* OutputNeuron : OutputLayer)
	{
		const float Value = OutputNeuron->Evaluate();
		TotalOutput += Value;
		EvaluatedOutputLayer.Add(Value);
	}

	if (TotalOutput <= 0.0f)
	{
		return TArray<bool>();
	}

	int32 MaxOutputIndex = 0;
	float MaxValue = -1.0f;

	for (int32 OutputIndex = 0; OutputIndex < OutputLayer.Num(); ++OutputIndex)
	{
		const float NormalizedValue = EvaluatedOutputLayer[OutputIndex] / TotalOutput;
		if (NormalizedValue > MaxValue)
		{
			MaxValue = NormalizedValue;
			MaxOutputIndex = OutputIndex;
		}
	}

	TArray<bool> ActiveOutputs;
	ActiveOutputs.Init(false, OutputLayer.Num());
	ActiveOutputs[MaxOutputIndex] = true;

	return ActiveOutputs;
}

const FSG_Genome& USG_NeuralNetwork::GetGenome() const
{
	return Genome;
}

void USG_NeuralNetwork::SetGenome(const FSG_Genome& InGenome)
{
	Genome = InGenome;
	bNewGenome = true;
}

void USG_NeuralNetwork::SetInputs(const TArray<float>& Inputs)
{
	if (InputLayer.Num() != Inputs.Num())
	{
		return;
	}

	for (int32 InputIndex = 0; InputIndex < InputLayer.Num(); ++InputIndex)
	{
		InputLayer[InputIndex]->SetValue(Inputs[InputIndex]);
	}
}

void USG_NeuralNetwork::SetConnectionWeights(const TArray<float>& ConnectionWeights)
{
	if (ConnectionWeights.Num() != (InputToHiddenConnections.Num() + HiddenToOutputConnections.Num()))
	{
		return;
	}

	for (int32 Index = 0; Index < ConnectionWeights.Num(); ++Index)
	{
		const float Weight = ConnectionWeights[Index];

		if (Index < InputToHiddenConnections.Num())
		{
			InputToHiddenConnections[Index]->SetWeight(Weight);
		}
		else
		{
			HiddenToOutputConnections[Index - InputToHiddenConnections.Num()]->SetWeight(Weight);
		}
	}
}

void USG_NeuralNetwork::UpdateWeights()
{
	if (bNewGenome)
	{
		SetConnectionWeights(Genome);
		bNewGenome = false;
	}
}
