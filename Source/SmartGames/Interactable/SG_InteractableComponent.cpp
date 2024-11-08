#include "SmartGames/Interactable/SG_InteractableComponent.h"

#include "MovieSceneSequencePlayer.h"
#include "TemplateSequence.h"
#include "TemplateSequenceActor.h"
#include "TemplateSequencePlayer.h"
#include "SmartGames/BDI/Agent/SG_Agent.h"

bool USG_InteractableComponent::IsAvailable() const
{
	return !TargetAgent;
}

void USG_InteractableComponent::PreInteraction(ASG_Agent* Agent)
{
	TargetAgent = Agent;
}

void USG_InteractableComponent::StartInteraction()
{
	if (!TargetSequence || !TargetAgent)
	{
		PostInteraction();
		return;
	}

	FMovieSceneSequencePlaybackSettings Settings;
	UTemplateSequencePlayer::CreateTemplateSequencePlayer(this, TargetSequence, Settings, TargetSequenceActor);
	TargetSequenceActor->SetBinding(TargetAgent);
	TargetSequenceActor->SequencePlayer->OnFinished.AddDynamic(this, &USG_InteractableComponent::OnTargetSequenceEnded);
	TargetSequenceActor->SequencePlayer->Play();
}

void USG_InteractableComponent::PostInteraction()
{
	if (TargetAgent)
	{
		TargetAgent->UpdateBelief(Reward);
		TargetAgent = nullptr;
	}
	
	if (TargetSequenceActor)
	{
		TargetSequenceActor->SequencePlayer->OnFinished.RemoveAll(this);
		TargetSequenceActor = nullptr;
	}
	
	OnInteractionCompleted.Broadcast();
}

bool USG_InteractableComponent::HasReward(const FSG_Belief& InReward, ESG_ComparisonOperator ComparisonOperator) const
{
	if (Reward.Type != InReward.Type)
	{
		return false;
	}

	switch (ComparisonOperator)
	{
	case ESG_ComparisonOperator::Equal:
		return FMath::IsNearlyEqual(Reward.Value, InReward.Value);
	case ESG_ComparisonOperator::NotEqual:
		return !FMath::IsNearlyEqual(Reward.Value, InReward.Value);
	case ESG_ComparisonOperator::Greater:
		return Reward.Value > InReward.Value;
	case ESG_ComparisonOperator::GreaterOrEqual:
		return Reward.Value >= InReward.Value;
	case ESG_ComparisonOperator::Less:
		return Reward.Value < InReward.Value;
	case ESG_ComparisonOperator::LessOrEqual:
		return Reward.Value <= InReward.Value;
	default:
		break;
	}

	return false;
}

void USG_InteractableComponent::OnTargetSequenceEnded()
{
	PostInteraction();
}
