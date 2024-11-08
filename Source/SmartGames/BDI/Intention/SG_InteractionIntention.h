#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "SmartGames/BDI/Belief/SG_Belief.h"
#include "SmartGames/BDI/Intention/SG_Intention.h"
#include "SmartGames/Utils/SG_ComparisonOperator.h"

#include "SG_InteractionIntention.generated.h"

class AActor;
class AAIController;
class ASG_Agent;
class USG_InteractableComponent;

// Interaction Intention
UCLASS()
class USG_InteractionIntention : public USG_Intention
{
	GENERATED_BODY()

public:
	virtual bool CanExecute() const override;
	virtual void Execute() override;

protected:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UFUNCTION()
	void OnInteractionCompleted();

	UFUNCTION()
	void OnInteractableDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	USG_InteractableComponent* FindInteractable() const;

	UPROPERTY(EditDefaultsOnly)
	FSG_Belief RewardToFind;
	
	UPROPERTY(EditDefaultsOnly)
	ESG_ComparisonOperator RewardRule { ESG_ComparisonOperator::Equal };

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius { 80.0f };

	UPROPERTY(EditDefaultsOnly)
	float SearchRadius { 5000.0f };

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> InteractableFinderChannel;

private:
	UPROPERTY(Transient, DuplicateTransient)
	AAIController* Controller { nullptr };

	UPROPERTY(Transient, DuplicateTransient)
	USG_InteractableComponent* Interactable { nullptr };
};