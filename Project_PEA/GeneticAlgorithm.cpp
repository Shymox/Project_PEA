#include "GeneticAlgorithm.h"
#include <iostream>
#include <time.h>
#include <random>

std::default_random_engine generator;

int random(int i) {
	std::uniform_int_distribution<int> distribution(0, i - 1);
	return distribution(generator);
}


double fRand(double fMin, double fMax)  // random double
{
	double f = (double)random(RAND_MAX) / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void GeneticAlgorithm::init(int** matrix, size_t size, int optimum,int period)
{
	generator.seed(time(NULL));
	this->best.cost = INT_MAX;
	this->period = period;
	this->iteration = 0;
	this->matrix = matrix;
	this->size = size-1;
	this->optimum = optimum;
	this->population = new std::vector<specimen>;
	this->populationBreading = new std::vector<specimen>;
	this->firstPopulation();
}

void GeneticAlgorithm::firstPopulation()
{
	for (int i = 0; i < POPULATIONSIZE; i++)
	{
		specimen specimen;
		for (int k = 0; k < this->size - 1; k++)
		{
			specimen.path.push_back( k + 1);
		}
		for (int k = 0; k < this->size - 2; k++)
		{
			int j = fRand(0.0, (this->size - 1 - k));
			int tmp = specimen.path[k];
			specimen.path[k] = specimen.path[j + k];
			specimen.path[j + k] = tmp;
		}
		specimen.cost = calcCost(specimen);
		this->checkIfBest(specimen);
		this->population->push_back(specimen);
	}
}

void GeneticAlgorithm::mutate(specimen &specimen)
{
	if (fRand(0.0,1.0) < this->mutationPropability)
	{
		size_t indexA = random(specimen.path.size() - 1);
		size_t indexB = random(specimen.path.size() - 1);
		int temp = specimen.path[indexA];
		specimen.path[indexA] = specimen.path[indexB];
		specimen.path[indexB] = temp;
	}
}
//inspiracja https://stackoverflow.com/questions/1544055/crossover-operation-in-genetic-algorithm-for-tsp/11584750#11584750


specimen GeneticAlgorithm::cross(specimen &parent1, specimen &parent2)
{
	specimen child;
	if (fRand(0.0,1.0) < crossoverPropability)
	{
		size_t crossStart =  random(this->size - 1);
		size_t crossEnd =  random(this->size - 1 - crossStart) + crossStart;
		child.path = parent1.path;
		int* map=new int[child.path.size()];
		for (int i = 0; i < child.path.size(); i++)
		{
			map[child.path[i]-1] = i;
		}
		for (int i = crossStart; i <= crossEnd; i++)
		{
			int newVal = parent2.path[i];
			int temp = child.path[map[newVal-1]];
			child.path[map[newVal-1]] = child.path[i];
			child.path[i] = temp;
			temp = map[child.path[map[newVal-1]]-1];
			map[child.path[map[newVal-1]]-1] = map[child.path[i]-1];
			map[child.path[i]-1] = temp;
		}
		delete[] map;
		/*size_t crossStart = random(this->size - 1);
		size_t crossEnd = random(this->size - 1 - crossStart) + crossStart;
		child.path = parent1.path;
		for (int i = crossStart; i <= crossEnd; i++)
		{
			int map=parent2.path[i];
			int old=child.path[i];
			for (int j = 0; i < child.path.size(); j++)
			{
				if (child.path[j] == map)
				{
					child.path[j] = old;
					child.path[i] = map;
					break;
				}
			} 
		}*/
	}
	else
	{
		child = parent1;
	}
	child.cost = calcCost(child);
	return child;
}


int GeneticAlgorithm::calcCost(specimen &specimen)
{
	int cost = 0;
	for (int i = 1; i < this->size - 1; i++)
	{
		cost += matrix[specimen.path[i - 1]][specimen.path[i]];
	}
	cost += matrix[0][specimen.path[0]];
	cost += matrix[specimen.path[this->size - 2]][0];
	return cost;
}

void GeneticAlgorithm::selectTournament()
{
	delete this->populationBreading;
	this->populationBreading = new std::vector<specimen>;
	for (int i = 0; i < POPULATIONSIZE; i++)
	{
		size_t parent1 = random(POPULATIONSIZE - 1);
		size_t parent2 = random(POPULATIONSIZE - 1);
		if (this->population->at(parent1).cost>this->population->at(parent2).cost)
		{
			this->populationBreading->push_back(this->population->at(parent2));
		}
		else
		{
			this->populationBreading->push_back(this->population->at(parent1));
		}
	}
}

void GeneticAlgorithm::makeNewPopulation()
{
	delete this->population;
	this->population = new std::vector<specimen>;
	for (int i = 0; i < this->POPULATIONSIZE/2;i++)
	{
		size_t parent1 = random(POPULATIONSIZE - 1);
		size_t parent2 = random(POPULATIONSIZE - 1);
		specimen child1 = cross(this->populationBreading->at(parent1), this->populationBreading->at(parent2));
		specimen child2 = cross(this->populationBreading->at(parent2), this->populationBreading->at(parent1));
		this->mutate(child1);
		this->mutate(child2);
		this->checkIfBest(child1);
		this->checkIfBest(child2);
		this->population->push_back(child1);
		this->population->push_back(child2);
	}
}

void GeneticAlgorithm::checkIfBest(specimen &specimen)
{
	if (specimen.cost < this->best.cost)
	{
		this->best.path = specimen.path;
		this->best.cost = specimen.cost;
		//std::cout << '\n' << iteration << " Cost: " << this->best.cost << " PRD: " << 100 * this->best.cost / this->optimum << '\n';
	}
}

void GeneticAlgorithm::copyPopulation(std::vector<specimen>* population)
{
	delete this->population;
	this->population = population;
}

void GeneticAlgorithm::loop()
{
	start = time(NULL);
	while (start+this->period>time(NULL))
	{
		this->selectTournament();
		this->makeNewPopulation();
		this->iteration++;
	}
}

void GeneticAlgorithm::displayBest()
{
	std::cout << "\n 0 ";
	for (size_t i = 0; i < this->size - 1; i++)
	{
		std::cout << this->best.path[i] << " ";
	}
	std::cout << "Cost: " << this->best.cost << " PRD:" << 100 * this->best.cost / this->optimum << '\n';
}

void GeneticAlgorithm::erase()
{
	delete this->population;
	delete this->populationBreading;
	this->population=nullptr;
	this->populationBreading=nullptr;
}

GeneticAlgorithm::GeneticAlgorithm(int** matrix, size_t size,int optimum,int period)
{
	this->init(matrix, size, optimum,period);
	this->loop();
	this->displayBest();
	
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	this->erase();
}
