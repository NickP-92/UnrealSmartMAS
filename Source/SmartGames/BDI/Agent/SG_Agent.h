#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SmartGames/ANN/SG_Genome.h"
#include "SmartGames/BDI/Belief/SG_Belief.h"
#include "SmartGames/BDI/Desire/SG_Desire.h"
#include "SmartGames/BDI/Intention/SG_Intention.h"

#include "SG_Agent.generated.h"

class USG_AgentBrainComponent;

// Agent
UCLASS()
class ASG_Agent : public ACharacter
{
	GENERATED_BODY()
	
public:
	ASG_Agent();

	virtual void Tick(float DeltaSeconds) override;

	const TArray<FSG_Belief>& GetBeliefs() const;
	void UpdateBelief(const FSG_Belief& InBelief);

	float GetFitness() const;
	void UpdateFitness();

	const FSG_Genome& GetGenome() const;
	void SetGenome(const FSG_Genome& InGenome);

	const TArray<USG_Intention*>& GetIntentions() const;

protected:
	UFUNCTION()
	void OnExecutionCompleted();

	USG_Intention* SelectNextIntention();
	void ExecuteIntention(USG_Intention* Intention);

	// What the agent knows
	UPROPERTY(EditDefaultsOnly, Category=Setup)
	TArray<FSG_Belief> Beliefs;
	
	// What the agent wants
	UPROPERTY(EditDefaultsOnly, Category=Setup)
	TArray<FSG_Desire> Desires;
	
	// What the agent can do
	UPROPERTY(EditDefaultsOnly, Instanced, Category=Setup)
	TArray<USG_Intention*> Intentions;

	UPROPERTY(VisibleAnywhere)
	USG_AgentBrainComponent* BrainComponent { nullptr };

private:
	float EvaluateDesire(const FSG_Desire& Desire) const;

	UPROPERTY(Transient, DuplicateTransient)
	USG_Intention* ActiveIntention { nullptr };

	float Fitness { 0.0f };
};