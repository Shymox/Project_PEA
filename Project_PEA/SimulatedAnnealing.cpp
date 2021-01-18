#include "SimulatedAnnealing.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Timer.h"



//obliczanie wariancji
float SimulatedAnnealing::calculateVariance()
{
	//std::cout << "\n List.size() " << list.size() << '\n';
	float average = 0;
	float upper = 0;
	for (this->id = this->list.begin(); this->id != this->list.end(); this->id++)
	{
		average+=*id;
	}
	average = average / this->list.size();
	for (this->id = this->list.begin(); this->id != this->list.end(); this->id++)
	{
		upper += pow(*id - average, 2);
	}
	if (list.size() == 0) return 0;
	return upper/this->list.size();
}

void SimulatedAnnealing::init(size_t size, int optimum)
{
	this->optimum = optimum;
	this->path = nullptr;
	this->pathBest = nullptr;
	this->Tmin = 0.0001;
	this->size = size;
	this->change = size;
	this->firstTemp();
	this->beta = (this->T - this->Tmin) / (this->maxit * this->T * this->Tmin);
}
//generowanie losowej �cie�ki
void SimulatedAnnealing::firstRandom(int** matrix)
{
	if (this->path != nullptr)
	{
		delete[] this->path;
	}
	this->cost = 0;
	this->path = new int[this->size-1];
	for (int i = 0; i < this->size-1; i++)
	{
		this->path[i] = i+1;
	}
	for (int i = 0; i < this->size - 2;i++)
	{
		int j = rand() % (this->size - 1 - i);
		int tmp = this->path[i];
		this->path[i] = this->path[j+i];
		this->path[j + i] = tmp;
	}
	for (int i = 1; i < this->size - 1; i++)
	{
		this->cost += matrix[this->path[i - 1]][this->path[i]];
	}
	this->cost += matrix[0][this->path[0]];
	this->cost += matrix[this->path[this->size-2]][0];
}
//obliczanie prawdopodobie�stwa
float SimulatedAnnealing::propability(int costCurrent, int cost)
{
	return std::exp(-((costCurrent-cost)/this->T));
}
//zamiana wierzcho�k�w z obliczeniem nowego kosztu
int SimulatedAnnealing::swap(int**matrix,int indexA, int indexB)
{
	int temp = this->path[indexA];
	this->path[indexA] = this->path[indexB];
	this->path[indexB] = temp;

	int cost = 0;
	for (int i = 1; i < this->size - 1; i++)
	{
		cost += matrix[this->path[i - 1]][this->path[i]];
	}
	cost += matrix[0][this->path[0]];
	cost += matrix[this->path[this->size - 2]][0];
	return cost;

	//if (indexA > indexB)
	//{
	//	int tmp = indexA;
	//	indexA = indexB;
	//	indexB = tmp;
	//}


	/*if (indexA!=0)
	{
		if (indexB != this -> size - 2)
		{
			return this->cost + matrix[this->path[indexA - 1]][this->path[indexA]] 
				+ matrix[this->path[indexA]][this->path[indexA + 1]]
				+ matrix[this->path[indexB - 1]][this->path[indexB]]
				+ matrix[this->path[indexB]][this->path[indexB+1]]
				- matrix[this->path[indexA - 1]][this->path[indexB]]
				- matrix[this->path[indexB]][this->path[indexA + 1]]
				- matrix[this->path[indexB-1]][this->path[indexA]]
				- matrix[this->path[indexA]][this->path[indexB+1]];

		}
		else
		{
			return this->cost + matrix[this->path[indexA - 1]][this->path[indexA]]
				+ matrix[this->path[indexA]][this->path[indexA+1]]
				+ matrix[this->path[indexB - 1]][this->path[indexB]]
				+ matrix[this->path[indexB]][0]
				- matrix[this->path[indexA-1]][this->path[indexB]]
				- matrix[this->path[indexB]][this->path[indexA + 1]]
				- matrix[this->path[indexA]][0]
				- matrix[this->path[indexB-1]][this->path[indexA]];
		}
	}
	else
	{
		if (indexB != this->size - 2)
		{
			int cost;
			cost = this->cost;
			cost+= matrix[0][this->path[indexA]];
			cost += matrix[this->path[indexA]][this->path[indexA + 1]];
			cost += matrix[this->path[indexB - 1]][this->path[indexB]];
			cost += matrix[this->path[indexB]][this->path[indexB + 1]];
			cost += -matrix[0][this->path[indexB]];
			std::cout << matrix[this->path[indexB]][this->path[indexA + 1]];
			cost += -matrix[this->path[indexB]][this->path[indexA + 1]];
			cost += -matrix[this->path[indexB - 1]][this->path[indexA]];
			cost +=	-matrix[this->path[indexA]][this->path[indexB + 1]];
			return cost;
		}
		else
		{
			return this->cost + matrix[0][this->path[indexA]]
				+ matrix[this->path[indexA]][this->path[indexA+1]]
				+ matrix[this->path[indexB - 1]][this->path[indexB]]
				+ matrix[this->path[indexB]][0]
				- matrix[0][this->path[indexB]]
				- matrix[this->path[indexB]][this->path[indexA + 1]]
				- matrix[this->path[indexB-1]][this->path[indexA]]
				- matrix[this->path[indexA]][0];
		}
	}*/
}
//nowy optymalny wynik
void SimulatedAnnealing::newBest()
{
	if (this->pathBest != nullptr)
	{
		delete[] this->pathBest;
	}
	this->pathBest = new int[this->size-1];
	for (size_t i = 0; i < this->size-1; i++)
	{
		this->pathBest[i] = this->path[i];
	}
	this->costBest = this->cost;
}
//pierwsza temperatura
void SimulatedAnnealing::firstTemp()
{
	this->T = 100;
}
//obliczenie nast�pnej temperatury 1
float SimulatedAnnealing::newTemp1()
{
	return this->T = this->T * 0.95;
}
//obliczenie nast�pnej temperatury 2
float SimulatedAnnealing::newTemp2()
{
	return this->T=this->T/(1+this->beta*this->T);
}

//losowanie warto�ci od 0 do 1
float SimulatedAnnealing::random()
{
	return static_cast<float>(rand()) / RAND_MAX;
}


//p�tla dla wyboru 0 w menu
void SimulatedAnnealing::loop1(int** matrix, size_t size)
{
	int i = 0;
	this->newBest();
	while (this->T > this->Tmin && i < maxit)
	{
		int indexA = rand() % (size - 1);
		int indexB = rand() % (size - 1);
		if (indexA != indexB)
		{
			this->costCurrent = this->swap(matrix, indexA, indexB);
			if (this->cost > this->costCurrent || this->random() < this->propability(this->costCurrent, this->cost))
			{
				this->cost = this->costCurrent;
				this->list.push_front(this->cost);
				if (this->list.size() > 100)
				{
					this->list.pop_back();
				}
				if (this->cost < this->costBest)
				{
					this->newBest();
					//std::cout << '\n' << i << " Cost: " << this->costBest << " PRD: " << 100 * this->costBest / this->optimum << '\n';
				}
			}
			else {

				this->swap(matrix, indexA, indexB);
			}
			this->T = newTemp1();
			i++;
			if (this->list.size() >= 100 && this->calculateVariance() < 10)
			{
				this->T += this->change;
				this->change = this->change * 1.25;
				this->firstRandom(matrix);
			}
		}

	}
}
//P�tla dla wyboru 1 w menu
void SimulatedAnnealing::loop2(int** matrix, size_t size)
{
	int i = 0;
	this->newBest();
	while (this->T > this->Tmin && i < maxit)
	{
		int indexA = rand() % (size - 1);
		int indexB = rand() % (size - 1);
		if (indexA != indexB)
		{
			this->costCurrent = this->swap(matrix, indexA, indexB);
			if (this->cost > this->costCurrent || this->random() < this->propability(this->costCurrent, this->cost))
			{
				this->cost = this->costCurrent;
				this->list.push_front(this->cost);
				if (this->list.size() > 100)
				{
					this->list.pop_back();
				}
				if (this->cost < this->costBest)
				{
					this->newBest();
					//std::cout << '\n' << i <<" Cost: "<<this->costBest<< " PRD: " << 100 * this->costBest / this->optimum << '\n';
				}
			}
			else {

				this->swap(matrix, indexA, indexB);
			}
			this->T = newTemp2();
			i++;
			if (this->list.size() >= 100 && this->calculateVariance() < 10)
			{
				this->T += this->change;
				this->change = this->change * 1.25;
				this->firstRandom(matrix);
			}
		}
	}
}

void SimulatedAnnealing::display()
{
	std::cout << "\n 0 ";
	for (size_t i = 0; i < this->size-1; i++)
	{
		std::cout << this->path[i]<<" ";
	}
	std::cout << "Cost: " << this->cost;
}

void SimulatedAnnealing::displayBest()
{
	std::cout << "\n 0 ";
	for (size_t i = 0; i < this->size - 1; i++)
	{
		std::cout << this->pathBest[i] << " ";
	}
	std::cout << "Cost: " << this->costBest<<" PRD:"<< 100 * this->costBest / this->optimum<<'\n';
}


SimulatedAnnealing::SimulatedAnnealing(int** matrix, size_t size,int optimum,int select)
{
	Timer* timer = new Timer();
	int prd=0;
	int prd2 = 0;
	float time=0;
	float time2 = 0;
	timer->startCounter();
	this->init(size,optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop1(matrix, size);
	time+=timer->getCounter();
	this->displayBest();
	prd+= 100 * this->costBest/optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop1(matrix, size);
	time += timer->getCounter();
	this->displayBest();
	prd += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop1(matrix, size);
	time += timer->getCounter();
	this->displayBest();
	prd += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop1(matrix, size);
	time += timer->getCounter();
	this->displayBest();
	prd += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop1(matrix, size);
	time += timer->getCounter();
	this->displayBest();
	prd += 100 * this->costBest / optimum;
	std::cout << "PRD: " << prd/5 << " czas: " << static_cast<float>(time)/5;
	//else

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop2(matrix, size);
	time2 += timer->getCounter();
	this->displayBest();
	prd2 += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop2(matrix, size);
	time2 += timer->getCounter();
	this->displayBest();
	prd2 += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop2(matrix, size);
	time2 += timer->getCounter();
	this->displayBest();
	prd2 += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop2(matrix, size);
	time2 += timer->getCounter();
	this->displayBest();
	prd2 += 100 * this->costBest / optimum;

	timer->startCounter();
	this->init(size, optimum);
	this->firstRandom(matrix);
	//if (select == 0)
	this->loop2(matrix, size);
	time2 += timer->getCounter();
	this->displayBest();
	prd2 += 100*this->costBest / optimum;

	std::cout << "PRD: " << prd2 / 5 << " czas: " << static_cast<float>(time2) / 5;
	
}

SimulatedAnnealing::~SimulatedAnnealing()
{
	if (this->path != nullptr)
	{
		delete[] this->path;
		this->path = nullptr;
	}
	if (this->pathBest != nullptr)
	{
		delete[] this->pathBest;
		this->pathBest = nullptr;
	}
}
