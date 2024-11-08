#include "SmartGames/BDI/Agent/SG_AgentBrainComponent.h"

#include "SmartGames/BDI/Agent/SG_Agent.h"
#include "SmartGames/BDI/Belief/SG_Belief.h"
#include "SmartGames/BDI/Intention/SG_Intention.h"
#include "SmartGames/ANN/SG_NeuralNetwork.h"

USG_Intention* USG_AgentBrainComponent::SelectNextIntention()
{
    if (!NeuralNetwork)
    {
        NeuralNetwork = CreateNeuralNetwork();
    }

    return DecodeNetworkOutput(RunNetwork());
}

const FSG_Genome& USG_AgentBrainComponent::GetGenome() const
{
    return NeuralNetwork->GetGenome();
}

void USG_AgentBrainComponent::SetGenome(const FSG_Genome& InGenome)
{
    NeuralNetwork->SetGenome(InGenome);
}

USG_NeuralNetwork* USG_AgentBrainComponent::CreateNeuralNetwork() const
{
    ASG_Agent* OwnerAgent = GetOwnerAgent();
    if (!OwnerAgent)
    {
        return nullptr;
    }

    const int32 BeliefNum = OwnerAgent->GetBeliefs().Num();
    const int32 IntentionNum = OwnerAgent->GetIntentions().Num();
    const int32 InputNum = BeliefNum + IntentionNum;
    const int32 OutputNum = IntentionNum;
    const int32 HiddenNum = InputNum * 0.5f;

    return USG_NeuralNetwork::CreateNeuralNetwork(InputNum, HiddenNum, OutputNum);
}

TArray<float> USG_AgentBrainComponent::EncodeBeliefs() const
{
    ASG_Agent* OwnerAgent = GetOwnerAgent();
    if (!OwnerAgent)
    {
        return {};
    }

    TArray<float> EncodedBeliefs;
    for (const FSG_Belief& Belief : OwnerAgent->GetBeliefs())
    {
        EncodedBeliefs.Add(Belief.Evaluate());
    }

    return EncodedBeliefs;
}

TArray<float> USG_AgentBrainComponent::EncodeIntentions() const
{
    ASG_Agent* OwnerAgent = GetOwnerAgent();
    if (!OwnerAgent)
    {
        return {};
    }

    TArray<float> EncodedIntentions;
    for (const USG_Intention* Intention : OwnerAgent->GetIntentions())
    {
        if (Intention)
        {
            EncodedIntentions.Add(Intention->Evaluate());
        }
    }

    return EncodedIntentions;
}

TArray<float> USG_AgentBrainComponent::GenerateNetworkInputs() const
{
    TArray<float> Inputs;
    Inputs.Append(EncodeBeliefs());
    Inputs.Append(EncodeIntentions());
    return Inputs;
}

TArray<bool> USG_AgentBrainComponent::RunNetwork()
{
    return NeuralNetwork ? NeuralNetwork->Run(GenerateNetworkInputs()) : TArray<bool>();
}

USG_Intention* USG_AgentBrainComponent::DecodeNetworkOutput(const TArray<bool>& Output) const
{
    ASG_Agent* OwnerAgent = GetOwnerAgent();
    TArray<USG_Intention*> Intentions = OwnerAgent ? OwnerAgent->GetIntentions() : TArray<USG_Intention*>();

    if (Output.Num() != Intentions.Num())
    {
        return nullptr;
    }

    for (int32 Index = 0; Index < Output.Num(); ++Index)
    {
        if (Output[Index])
        {
            return Intentions[Index];
        }
    }

    return nullptr;
}

ASG_Agent* USG_AgentBrainComponent::GetOwnerAgent() const
{
    return Cast<ASG_Agent>(GetOuter());
}
