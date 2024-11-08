#include "SmartGames/BDI/Intention/SG_IdleIntention.h"

#include "MovieSceneSequencePlayer.h"
#include "TemplateSequence.h"
#include "TemplateSequenceActor.h"
#include "TemplateSequencePlayer.h"
#include "SmartGames/BDI/Agent/SG_Agent.h"

bool USG_IdleIntention::CanExecute() const
{
    return true;
}

void USG_IdleIntention::Execute()
{
	ASG_Agent* OwnerAgent = GetOwnerAgent();
	if (!OwnerAgent)
	{
		CompleteExecution();
		return;
	}

	FMovieSceneSequencePlaybackSettings Settings;
	UTemplateSequencePlayer::CreateTemplateSequencePlayer(this, IdleSequence, Settings, SequenceActor);
	SequenceActor->SetBinding(OwnerAgent);
	SequenceActor->SequencePlayer->OnFinished.AddDynamic(this, &USG_IdleIntention::OnSequenceEnded);
	SequenceActor->SequencePlayer->Play();
}

void USG_IdleIntention::OnSequenceEnded()
{
    CompleteExecution();
}
