#include "SmartGames/Search/SG_GeneticAlgorithm.h"

#include "Algo/Sort.h"

#include "SmartGames/BDI/Agent/SG_Agent.h"

void USG_GeneticAlgorithm::Search(TArray<ASG_Agent*>& Population) const
{
	const TArray<FSG_GenomeFitness> PopulationFitness = Evaluation(Population);
	const TArray<FSG_Genome> SelectedGenomes = Selection(PopulationFitness);
	TArray<FSG_Genome> NewGenomes = Crossover(SelectedGenomes);
	Mutation(NewGenomes);
	ApplyGenomes(Population, NewGenomes);
}

TArray<FSG_GenomeFitness> USG_GeneticAlgorithm::Evaluation(const TArray<ASG_Agent*>& Population) const
{
	TArray<FSG_GenomeFitness> PopulationFitness;
	PopulationFitness.Reserve(Population.Num());

	for (ASG_Agent* Agent : Population)
	{
		Agent->UpdateFitness();

		FSG_GenomeFitness GenomeFitness;
		GenomeFitness.Genome = Agent->GetGenome();
		GenomeFitness.Fitness = Agent->GetFitness();
		PopulationFitness.Add(GenomeFitness);
	}

	Algo::SortBy(PopulationFitness, &FSG_GenomeFitness::Fitness, TGreater<>());

	float CumulativeFitness = 0.0f;
	for (int32 Index = 0; Index < PopulationFitness.Num(); ++Index)
	{
		CumulativeFitness += (Index / PopulationFitness.Num());
		PopulationFitness[Index].Fitness = CumulativeFitness;
	}

	return PopulationFitness;
}

TArray<FSG_Genome> USG_GeneticAlgorithm::Selection(const TArray<FSG_GenomeFitness>& PopulationFitness) const
{
	TArray<FSG_Genome> SelectedGenomes;
	SelectedGenomes.Reserve(PopulationFitness.Num());

	const float Min = PopulationFitness[0].Fitness;
	const float Max = PopulationFitness.Last().Fitness;

	for (int32 Count = 0; Count < PopulationFitness.Num(); ++Count)
	{
		const float ExtractionValue = (FMath::FRand() * (Max - Min)) + Min;

		for (const FSG_GenomeFitness& GenomeFitness : PopulationFitness)
		{
			if (GenomeFitness.Fitness >= ExtractionValue)
			{
				SelectedGenomes.Add(GenomeFitness.Genome);
				break;
			}
		}
	}

	return SelectedGenomes;
}

TArray<FSG_Genome> USG_GeneticAlgorithm::Crossover(const TArray<FSG_Genome>& Genomes) const
{
	TArray<FSG_Genome> NewGenomes;
	NewGenomes.Reserve(Genomes.Num());

	for (int32 Index = 0; Index < Genomes.Num(); Index += 2)
	{
		if (FMath::FRand() < CrossoverProb)
		{
			continue;
		}

		const FSG_Genome FirstGenome = Genomes[Index];
		const FSG_Genome SecondGenome = Genomes[Index + 1];
		const int32 CutPoint = FMath::RandRange(0, FirstGenome.Num());

		for (int32 GenomeIndex = 0; GenomeIndex < FirstGenome.Num(); ++GenomeIndex)
		{
			FSG_Genome FirstChildGenome;
			FirstChildGenome.Reserve(FirstGenome.Num());
			FSG_Genome SecondChildGenome;
			SecondChildGenome.Reserve(FirstGenome.Num());

			const float FirstValue = (GenomeIndex < CutPoint) ? FirstGenome[GenomeIndex] : SecondChildGenome[GenomeIndex];
			const float SecondValue = (GenomeIndex < CutPoint) ? SecondGenome[GenomeIndex] : FirstChildGenome[GenomeIndex];
			FirstChildGenome[GenomeIndex] = FirstValue;
			SecondChildGenome[GenomeIndex] = SecondValue;

			NewGenomes.Add(FirstChildGenome);
			NewGenomes.Add(SecondChildGenome);
		}
	}

	return NewGenomes;
}

void USG_GeneticAlgorithm::Mutation(TArray<FSG_Genome>& Genomes) const
{
	for (FSG_Genome& Genome : Genomes)
	{
		for (int32 Index = 0; Index < Genome.Num(); ++Index)
		{
			if (FMath::FRand() < MutationProb)
			{
				continue;
			}

			Genome[Index] += (MutationDev * ((FMath::FRand() * 2.0f) - 1.0f));
		}
	}
}

void USG_GeneticAlgorithm::ApplyGenomes(const TArray<ASG_Agent*>& Population, const TArray<FSG_Genome>& Genomes) const
{
	for (int32 Index = 0; Index < Population.Num(); ++Index)
	{
		Population[Index]->SetGenome(Genomes[Index]);
	}
}
