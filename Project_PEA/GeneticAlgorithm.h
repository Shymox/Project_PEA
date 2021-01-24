#include <vector>
#include <random>
#pragma once
 


struct specimen
{
	int cost;
	std::vector<int>path;
};

class GeneticAlgorithm
{
private:
	time_t start;
	double mutationPropability = 0.01;
	double crossoverPropability = 0.7;
	int POPULATIONSIZE=100;
	specimen best;
	size_t size;
	std::vector<specimen>* population;
	std::vector<specimen>* populationBreading;
	int** matrix;
	int optimum;
	size_t iteration;
	int period;

public:
	void init(int** matrix, size_t size,int optimum,int period);

	void firstPopulation();

	void mutate(specimen &specimen);;

	specimen cross(specimen &parent1,specimen &parent2);

	int calcCost(specimen &specimen);

	void selectTournament();

	void makeNewPopulation();

	void checkIfBest(specimen &specimen);

	void copyPopulation(std::vector<specimen>* population);

	void loop();

	void displayBest();

	void erase();


	GeneticAlgorithm(int** matrix, size_t size,int optimum,int period);

	~GeneticAlgorithm();
	
};

