#include "AntAlgorithm.h"
#include <iostream>
#include <time.h>
#include <random>

std::default_random_engine generatora;

int randoma(int i) {
	std::uniform_int_distribution<int> distribution(0, i - 1);
	return distribution(generatora);
}


double fRanda(double fMin, double fMax)  // random double
{
	double f = (double)randoma(RAND_MAX) / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


void AntAlgorithm::init(int** matrix, size_t size, int optimum, int period, int antsNumber, int startPheromone, float evaporation, float constant)
{
	this->alpha = 1;
	this->beta = 5;
	antsNumber = size;
	constant = 1;
	this->ants = nullptr;
	this->constant = constant;
	this->evaporation = evaporation;
	this->ants = new std::vector<ant>(antsNumber);
	generatora.seed(time(NULL));
	this->antsNumber = antsNumber;
	this->best.cost = INT_MAX;
	this->period = period;
	this->iteration = 0;
	this->matrix = matrix;
	this->size = size;
	this->optimum = optimum;
	startPheromone = size / optimum;
	this->pheromones = new float* [size];
	this->visited = new bool [size];
	for(int i=0; i<size;i++)
	{
		this->pheromones[i] = new float[size];
		for (int j = 0; j < size; j++)
		{
			if (i != j)
			{
				this->pheromones[i][j] = startPheromone;
			}
			else
			{
				this->pheromones[i][j] = 0;
			}
		}
	}
}

double AntAlgorithm::propability(size_t start, size_t end)
{
	return pow(1/(double)this->matrix[start][end],this->beta)*pow(this->pheromones[start][end],this->alpha);
}

double AntAlgorithm::sum(int start)
{
	double sum = 0.0;
	for (int i = 0; i < this->size; i++)
	{
		if (!this->visited[i])
			sum += pow(1/(double)this->matrix[start][i], this->beta) * pow(this->pheromones[start][i],this->alpha);
	}
	return sum;
}

void AntAlgorithm::isBest(ant ant)
{
	if (ant.cost < this->best.cost)
	{
		this->best.cost = ant.cost;
		this->best.path = ant.path;
		std::cout << '\n' << iteration << " Cost: " << this->best.cost << " PRD: " << 100 * this->best.cost / this->optimum << '\n';
	}
}

void AntAlgorithm::newIteration()
{
	for (int i = 0; i < this->antsNumber; i++)
	{
		(*this->ants)[i]=this->nextAnt();
	}
}

void AntAlgorithm::evaporate()
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (i != j)
				this->pheromones[i][j] *= this->evaporation;
		}
	}
}


ant AntAlgorithm::nextAnt()
{
	ant ant;
	ant.path.reserve(this->size);
	int cost = 0;
	
	for (int i = 0; i < this->size; i++)
	{
		this->visited[i] = false;
	}

	ant.path.push_back(randoma(this->size-1));
	this->visited[ant.path[0]] = true;
	for (int j = 1; j < this->size; j++)
	{
		double number = fRanda(0.0, 1.0);
		number *= this->sum(ant.path[j - 1]);
		double prop = 0.0;
		for (int i = 0; i < this->size; i++)
		{
			if (!visited[i])
			{
				prop += propability(ant.path.back(), i);
				if (prop >= number)
				{
					this->visited[i] = true;
					cost += this->matrix[ant.path.back()][i];
					ant.path.push_back(i);
					break;
				}
			}
		}
	}
	cost+= this->matrix[ant.path.back()][ant.path.front()];
	ant.cost = cost;
	this->isBest(ant);
	return ant;
}



void AntAlgorithm::updatePheronome()
{
	this->evaporate();

	for (int i = 0; i < this->antsNumber; i++)
	{
		for (int j = 0; j < this->size-1; j++)
		{
			this->pheromones[this->ants->at(i).path[j]][this->ants->at(i).path[j+1]]+= this->constant/ static_cast<float>(this->ants->at(i).cost);
		}
		this->pheromones[this->ants->at(i).path[this->size - 1]][this->ants->at(i).path[0]] = this->constant / static_cast<float>(this->ants->at(i).cost);
	}
}

void AntAlgorithm::loop()
{
	this->iteration = 0;
	start = time(NULL);
	while (start + this->period > time(NULL))
	{
		this->newIteration();
		this->updatePheronome();
		this->iteration++;
	}
}

void AntAlgorithm::displayBest()
{

	for (size_t i = 0; i < this->size; i++)
	{
		std::cout << this->best.path[i] << " ";
	}
	std::cout << "Cost: " << this->best.cost << " PRD:" << 100 * this->best.cost / this->optimum << '\n';
}

AntAlgorithm::AntAlgorithm(int** matrix, size_t size, int optimum, int period, int antsNumber, int startPheromone, float evaporation, float constant)
{
	this->init(matrix, size, optimum, period, antsNumber, startPheromone, evaporation, constant);
	this->loop();
	this->displayBest();
}

AntAlgorithm::~AntAlgorithm()
{
	for (int i = 0; i < this->size; i++)
	{
		delete[] this->pheromones[i];
		delete[] this->matrix[i];
	}
	delete[] this->pheromones;
	delete[] this->matrix;
	delete[] this->visited;
	delete ants;
}
