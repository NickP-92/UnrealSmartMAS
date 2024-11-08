#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "SG_Neuron.generated.h"

class USG_Connection;

// Neuron
UCLASS()
class USG_Neuron : public UObject
{
	GENERATED_BODY()

public:
	void AddInputConnection(USG_Connection* Connection);
	void AddOutputConnection(USG_Connection* Connection);
	
	virtual float Evaluate() PURE_VIRTUAL(USG_Neuron::Evaluate, return 0.0f;);

protected:
	UPROPERTY()
	TArray<USG_Connection*> InputConnections;

	UPROPERTY()
	TArray<USG_Connection*> OutputConnections;
};