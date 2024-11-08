#pragma once

#include "CoreMinimal.h"
#include "SmartGames/BDI/Intention/SG_Intention.h"

#include "SG_IdleIntention.generated.h"

class ASG_Agent;
class ATemplateSequenceActor;
class UTemplateSequence;

// Idle Intention
UCLASS()
class USG_IdleIntention : public USG_Intention
{
	GENERATED_BODY()

public:
	virtual bool CanExecute() const override;
	virtual void Execute() override;

protected:
	UFUNCTION()
	void OnSequenceEnded();

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	UTemplateSequence* IdleSequence { nullptr };

private:
	UPROPERTY(Transient, DuplicateTransient)
	ATemplateSequenceActor* SequenceActor { nullptr };
};