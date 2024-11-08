#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SmartGames/ANN/SG_Genome.h"

#include "SG_AgentBrainComponent.generated.h"

class ASG_Agent;
class USG_Intention;
class USG_NeuralNetwork;

// AgentBrain Component
UCLASS()
class USG_AgentBrainComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USG_Intention* SelectNextIntention();

	const FSG_Genome& GetGenome() const;
	void SetGenome(const FSG_Genome& InGenome);

protected:
	USG_NeuralNetwork* CreateNeuralNetwork() const;

	TArray<float> EncodeBeliefs() const;
	TArray<float> EncodeIntentions() const;
	TArray<float> GenerateNetworkInputs() const;
	TArray<bool> RunNetwork();
	USG_Intention* DecodeNetworkOutput(const TArray<bool>& Output) const;

	ASG_Agent* GetOwnerAgent() const;

private:
	UPROPERTY(Transient, DuplicateTransient)
	USG_NeuralNetwork* NeuralNetwork { nullptr };
};