#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SmartGames/ANN/SG_Genome.h"

#include "SG_NeuralNetwork.generated.h"

class USG_Connection;
class USG_InputNeuron;
class USG_Neuron;
class USG_SimpleNeuron;

// Neural Network
UCLASS()
class USG_NeuralNetwork : public UObject
{
	GENERATED_BODY()

public:
	static USG_NeuralNetwork* CreateNeuralNetwork(int32 InputNum, int32 HiddenNum, int32 OutputNum);

	TArray<bool> Run(const TArray<float>& Inputs);

	const FSG_Genome& GetGenome() const;
	void SetGenome(const FSG_Genome& InGenome);

protected:
	template<class T>
	static TArray<T*> CreateLayer(int32 NeuronNum);

	template<class T, class U>
	static void ConnectLayers(const TArray<T*>& FirstLayer, const TArray<U*>& SecondLayer, TArray<USG_Connection*>& Connections);

	void SetInputs(const TArray<float>& Inputs);
	void SetConnectionWeights(const TArray<float>& ConnectionWeights);

	void UpdateWeights();

	UPROPERTY()
	TArray<USG_InputNeuron*> InputLayer;

	UPROPERTY()
	TArray<USG_SimpleNeuron*> HiddenLayer;

	UPROPERTY()
	TArray<USG_SimpleNeuron*> OutputLayer;

	UPROPERTY()
	TArray<USG_Connection*> InputToHiddenConnections;

	UPROPERTY()
	TArray<USG_Connection*> HiddenToOutputConnections;

	bool bNewGenome { true };
	FSG_Genome Genome {};
};