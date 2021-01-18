#include "GeneticAlgorithm.h"
#include <iostream>
#include <time.h>

void GeneticAlgorithm::init(int** matrix, size_t size, int optimum)
{
	this->best.cost = INT_MAX;
	this->matrix = matrix;
	this->size = size-1;
	this->optimum = optimum;
	this->population = new std::vector<specimen>;
	this->populationBreading = new std::vector<specimen>;
	srand(time(NULL));
	this->firstPopulation();
}

void GeneticAlgorithm::firstPopulation()
{
	for (int i = 0; i < POPULATIONSIZE; i++)
	{
		specimen specimen;
		for (int i = 0; i < this->size - 1; i++)
		{
			specimen.path.push_back( i + 1);
		}
		for (int i = 0; i < this->size - 2; i++)
		{
			int j = rand() % (this->size - 1 - i);
			int tmp = specimen.path[i];
			specimen.path[i] = specimen.path[j + i];
			specimen.path[j + i] = tmp;
		}
		specimen.cost = calcCost(specimen);
		this->checkIfBest(specimen);
		this->population->push_back(specimen);
	}
}

void GeneticAlgorithm::mutate(specimen &specimen)
{
	if (rand() % RAND_MAX > this->mutationPropability)
	{
		size_t indexA = rand() % (specimen.path.size() - 1);
		size_t indexB = rand() % (specimen.path.size() - 1);
		int temp = specimen.path[indexA];
		specimen.path[indexA] = specimen.path[indexB];
		specimen.path[indexB] = temp;
	}
}

specimen GeneticAlgorithm::cross(specimen &parent1, specimen &parent2)
{
	specimen child;
	if (rand() % RAND_MAX > crossoverPropability)
	{
		size_t crossStart = rand() % (this->size - 1);
		size_t crossEnd = rand() % (this->size - 1 - crossStart) + crossStart;
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
		}
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
		size_t parent1 = rand() % (POPULATIONSIZE - 1);
		size_t parent2 = rand() % (POPULATIONSIZE - 1);
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
		size_t parent1 = rand()%(POPULATIONSIZE - 1);
		size_t parent2 = rand()%(POPULATIONSIZE - 1);
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
	while (start+15>time(NULL))
	{
		this->selectTournament();
		this->makeNewPopulation();
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

}

GeneticAlgorithm::GeneticAlgorithm(int** matrix, size_t size,int optimum)
{
	this->init(matrix, size, optimum);
	this->loop();
	this->displayBest();
	
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}
