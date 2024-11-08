#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "SmartGames/BDI/Belief/SG_Belief.h"
#include "SmartGames/Utils/SG_ComparisonOperator.h"

#include "SG_InteractableComponent.generated.h"

class ASG_Agent;
class ATemplateSequenceActor;
class UTemplateSequence;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSG_InteractableComponentDelegate);

// Interactable Component
UCLASS(Blueprintable)
class USG_InteractableComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	bool IsAvailable() const;
	void PreInteraction(ASG_Agent* Agent);
	void StartInteraction();
	void PostInteraction();
	bool HasReward(const FSG_Belief& InReward, ESG_ComparisonOperator ComparisonOperator) const;

	FSG_InteractableComponentDelegate OnInteractionCompleted;

protected:
	UFUNCTION()
	void OnTargetSequenceEnded();

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	UTemplateSequence* TargetSequence { nullptr };

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	FSG_Belief Reward;

private:
	UPROPERTY(Transient, DuplicateTransient)
	ATemplateSequenceActor* TargetSequenceActor { nullptr };

	UPROPERTY(Transient, DuplicateTransient)
	ASG_Agent* TargetAgent { nullptr };
};