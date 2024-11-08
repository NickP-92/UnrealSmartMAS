#include "SmartGames/BDI/Intention/SG_Intention.h"

#include "SmartGames/BDI/Agent/SG_Agent.h"

bool USG_Intention::CanExecute() const
{
	return false;
}

void USG_Intention::Execute()
{
}

float USG_Intention::Evaluate() const
{
	return CanExecute() ? 1.0f : 0.0f;
}

void USG_Intention::CompleteExecution()
{
	OnExecutionCompleted.Broadcast();
}

ASG_Agent* USG_Intention::GetOwnerAgent() const
{
	return Cast<ASG_Agent>(GetOuter());
}
