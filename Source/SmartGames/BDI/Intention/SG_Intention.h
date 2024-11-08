#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "SG_Intention.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSG_IntentionDelegate);

class ASG_Agent;

// Intention
UCLASS(Abstract, EditInlineNew, Blueprintable, CollapseCategories)
class USG_Intention : public UObject
{
	GENERATED_BODY()

public:
	virtual bool CanExecute() const;
	virtual void Execute();
	
	float Evaluate() const;

	FSG_IntentionDelegate OnExecutionCompleted;

protected:
	void CompleteExecution();
	ASG_Agent* GetOwnerAgent() const;
};