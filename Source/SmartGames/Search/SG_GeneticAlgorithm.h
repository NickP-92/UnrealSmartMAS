#pragma once

#include "CoreMinimal.h"
#include "SmartGames/ANN/SG_Genome.h"
#include "SmartGames/Search/SG_SearchAlgorithm.h"

#include "SG_GeneticAlgorithm.generated.h"

class ASG_Agent;

struct FSG_GenomeFitness
{
	FSG_Genome Genome {};
	float Fitness { 0.0f };
};

// Genetic algorithm
UCLASS()
class USG_GeneticAlgorithm : public USG_SearchAlgorithm
{
	GENERATED_BODY()

public:
	// USG_SearchAlgorithm START
	virtual void Search(TArray<ASG_Agent*>& Population) const override;
	// USG_SearchAlgorithm END

protected:
	TArray<FSG_GenomeFitness> Evaluation(const TArray<ASG_Agent*>& Population) const;
	TArray<FSG_Genome> Selection(const TArray<FSG_GenomeFitness>& PopulationFitness) const;
	TArray<FSG_Genome> Crossover(const TArray<FSG_Genome>& Genomes) const;
	void Mutation(TArray<FSG_Genome>& Genomes) const;
	void ApplyGenomes(const TArray<ASG_Agent*>& Population, const TArray<FSG_Genome>& Genomes) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossoverProb { 0.1f };
	
	UPROPERTY(EditDefaultsOnly)
	float MutationProb { 0.01f };
	
	UPROPERTY(EditDefaultsOnly)
	float MutationDev { 0.1f };
};