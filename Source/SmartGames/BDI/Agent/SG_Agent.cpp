#include "SmartGames/BDI/Agent/SG_Agent.h"

#include "SmartGames/BDI/Agent/SG_AgentBrainComponent.h"

ASG_Agent::ASG_Agent()
{
	BrainComponent = CreateDefaultSubobject<USG_AgentBrainComponent>(TEXT("BrainComponent"));
}

void ASG_Agent::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorTickEnabled(false);
	ExecuteIntention(SelectNextIntention());
}

const TArray<FSG_Belief>& ASG_Agent::GetBeliefs() const
{
	return Beliefs;
}

void ASG_Agent::UpdateBelief(const FSG_Belief& InBelief)
{
	for (FSG_Belief& Belief : Beliefs)
	{
		if (Belief.Type == InBelief.Type)
		{
			Belief.Value = FMath::Clamp(Belief.Value + InBelief.Value, Belief.Range.GetLowerBoundValue(), Belief.Range.GetUpperBoundValue());
			return;
		}
	}
}

float ASG_Agent::GetFitness() const
{
	return Fitness;
}

void ASG_Agent::UpdateFitness()
{
	Fitness = 0.0f;

	if (Desires.IsEmpty())
	{
		return;
	}

	for (const FSG_Desire& Desire : Desires)
	{
		Fitness += EvaluateDesire(Desire);
	}

	Fitness /= Desires.Num();
}

const FSG_Genome& ASG_Agent::GetGenome() const
{
	return BrainComponent->GetGenome();
}

void ASG_Agent::SetGenome(const FSG_Genome& InGenome)
{
	BrainComponent->SetGenome(InGenome);
}

const TArray<USG_Intention*>& ASG_Agent::GetIntentions() const
{
	return Intentions;
}

void ASG_Agent::OnExecutionCompleted()
{
	SetActorTickEnabled(true);

	if (ActiveIntention)
	{
		ActiveIntention->OnExecutionCompleted.RemoveAll(this);
		ActiveIntention = nullptr;
	}
}

USG_Intention* ASG_Agent::SelectNextIntention()
{
	return BrainComponent ? BrainComponent->SelectNextIntention() :  nullptr;
}

void ASG_Agent::ExecuteIntention(USG_Intention* Intention)
{
	if (Intention)
	{
		ActiveIntention = Intention;
		ActiveIntention->OnExecutionCompleted.AddDynamic(this, &ASG_Agent::OnExecutionCompleted);
		ActiveIntention->Execute();
	}
}

float ASG_Agent::EvaluateDesire(const FSG_Desire& Desire) const
{
	const FSG_Belief* Belief = Beliefs.FindByPredicate(
		[&](const FSG_Belief& Belief)
		{
			return Desire.BeliefType == Belief.Type;
		});

	if (!Belief)
	{
		return 0.0f;
	}

	const float Min = FMath::Min(Desire.FulfilledValue, Desire.UnfulfilledValue);
	const float Max = FMath::Max(Desire.FulfilledValue, Desire.UnfulfilledValue);
	const float BeliefValue = Belief->Value;

	return FMath::Clamp((BeliefValue - Min) / (Max - Min), Min, Max);
}
