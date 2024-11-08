#include "SmartGames/BDI/Intention/SG_InteractionIntention.h"

#include "Engine/World.h"
#include "AIController.h"
#include "SmartGames/BDI/Agent/SG_Agent.h"
#include "SmartGames/Interactable/SG_InteractableComponent.h"

bool USG_InteractionIntention::CanExecute() const
{
    return FindInteractable() != nullptr;
}

void USG_InteractionIntention::Execute()
{
    ASG_Agent* OwnerAgent = GetOwnerAgent();
    Interactable = FindInteractable();
    Controller = OwnerAgent ? OwnerAgent->GetController<AAIController>() : nullptr;

    if (!Interactable || !Controller)
    {
        CompleteExecution();
        return;
    }

    Interactable->PreInteraction(OwnerAgent);
    Interactable->GetOwner()->OnEndPlay.AddDynamic(this, &USG_InteractionIntention::OnInteractableDestroyed);

    Controller->ReceiveMoveCompleted.AddDynamic(this, &USG_InteractionIntention::OnMoveCompleted);
    Controller->MoveToActor(Interactable->GetOwner(), AcceptanceRadius);
}

void USG_InteractionIntention::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    Controller->ReceiveMoveCompleted.RemoveAll(this);
	
    if (Interactable)
    {
        Interactable->OnInteractionCompleted.AddDynamic(this, &USG_InteractionIntention::OnInteractionCompleted);
        Interactable->StartInteraction();
    }
    else
    {
        CompleteExecution();
    }
}

void USG_InteractionIntention::OnInteractionCompleted()
{
    if (Interactable)
    {
        Interactable->GetOwner()->OnEndPlay.RemoveAll(this);
        Interactable->OnInteractionCompleted.RemoveAll(this);
        Interactable->PostInteraction();
    }

    CompleteExecution();
}

void USG_InteractionIntention::OnInteractableDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
    OnInteractionCompleted();
}

USG_InteractableComponent* USG_InteractionIntention::FindInteractable() const
{
    AActor* OwnerAgent = GetOwnerAgent();
    UWorld* World = OwnerAgent ? OwnerAgent->GetWorld() : nullptr;

    if (!World)
    {
        return nullptr;
    }

    FCollisionShape SearchShape = FCollisionShape::MakeSphere(SearchRadius);
    TArray<FOverlapResult> Overlaps;

    World->OverlapMultiByChannel(Overlaps, OwnerAgent->GetActorLocation(), FQuat::Identity, InteractableFinderChannel, SearchShape);

    const FVector OwnerLocation = OwnerAgent->GetActorLocation();
    USG_InteractableComponent* ClosestInteractable = nullptr;

    for (const FOverlapResult& Overlap : Overlaps)
    {
        USG_InteractableComponent* OverlappedInteractable = Cast<USG_InteractableComponent>(Overlap.GetComponent());
        if (!OverlappedInteractable || !OverlappedInteractable->IsAvailable() || !OverlappedInteractable->HasReward(RewardToFind, RewardRule))
        {
            continue;
        }
		
        if (OverlappedInteractable && !ClosestInteractable)
        {
            ClosestInteractable = OverlappedInteractable;
            continue;
        }

        const FVector InteractableLocation = OverlappedInteractable->GetComponentLocation();
        const FVector ClosestInteractableLocation = ClosestInteractable->GetComponentLocation();
        if (FVector::DistSquared(InteractableLocation, OwnerLocation) < FVector::DistSquared(ClosestInteractableLocation, OwnerLocation))
        {
            ClosestInteractable = OverlappedInteractable;
        }
    }

    return ClosestInteractable;
}
