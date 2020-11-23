#include "DynamicProgramming.h"
#include <iostream>

//funkcja tworz¹ca tablice o wymiarach this->size na 2^(this->size)
void DynamicProgramming::init(size_t size)
{
	this->size = size;
	this->array = new  int*[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->array[i] = new int[this->pow(2, this->size)];
		for (int j = 0; j < this->pow(2, this->size); j++)
		{
			this->array[i][j] = 0;
		}
	}
	this->subsets = new Array();
}
//funkcja generuj¹ca wszystkie kombinacje dla zbioru wielkoœci this->size o r iloœci bitów ustawionych na 1
//w pierwszym kroku tworzona jest nowa dynamiczna tablica
Array* DynamicProgramming::combinations(int r)
{
	delete this->subsets;
	subsets = new Array();//utworzenie nowej pustej tablicy
	combinations(0,0,r);//rekurencyjne generowanie kombinacji
	return subsets;
}
//rekurencyjne generowanie kombinacji bitów
Array* DynamicProgramming::combinations(int set,int at,int r)
{
	if (r == 0)
	{
		this->subsets->pushBack(set);
	}
	else
	{
		for (int i = at; i < this->size; i++)
		{
			set = set | (1 << i);
			combinations(set,i+1,r-1);
			set = set & ~(1 << i);
		}
	}
	return this->subsets;
}
//funkcja sprawdzaj¹ca czy bit w podzbiorze o podanym numerze jest nie ustawiony na 1
bool DynamicProgramming::notIn(int i,int subset)
{
	return ((1 << i) & subset) == 0;
}
//funkcja wpisuj¹ca wartoœci pocz¹tkowe do tablicy trzymaj¹cej podzbiory
void DynamicProgramming::setup(int** matrix)
{
	for (int i = 0; i < this->size; i++)
	{
		if (i == this->START)
		{
			continue;
		}
		this->array[i][1 << this->START | 1 << i] = matrix[this->START][i];
	}
}

void DynamicProgramming::solve(int** matrix)
{
	for (int r = 3; r <= this->size; r++)
	{
		this->combinations(r);
		for (int i=0;i<this->subsets->returnSize();i++)
		{
			if (notIn(this->START, this->subsets->returnValue(i)))
			{
				continue;
			}
			for (int next = 0; next < this->size; next++)
			{
				if (next == this->START || notIn(next, this->subsets->returnValue(i)))
				{
					continue;
				}
				int state = this->subsets->returnValue(i) ^ (1 << next);
				int minDist = INT_MAX;
				for (int e = 0; e < this->size; e++)
				{
					if (e == this->START || e == next || notIn(e, this->subsets->returnValue(i)))
					{
						continue;
					}
					int newDistance = this->array[e][state] + matrix[e][next];
					if (newDistance < minDist)
					{
						minDist = newDistance;
					}
					this->array[next][this->subsets->returnValue(i)] = minDist;
				}
			}
		}
	}
}

//funkcja znajduj¹ca koszt minimalnej œcie¿ki
int DynamicProgramming::findMinCost(int** matrix)
{
	int END_STATE = ((1 << this->size) - 1);

	int minTourCost = INT_MAX;

	for (int e = 0; e < this->size; e++)
	{
		if (e == this->START)
		{
			continue;
		}
		int tourCost = this->array[e][END_STATE] + matrix[e][this->START];
		if (tourCost < minTourCost)
		{
			minTourCost = tourCost;
		}
	}
	return minTourCost;
}

//funkcja znajduj¹ca optymaln¹ œcie¿kê
int* DynamicProgramming::findOptimalTour(int** matrix)
{
	int lastIndex = this->START;
	int state = (1 << this->size) - 1;
	int* tour = new int[this->size + 1];

	for (int i = this->size - 1; i >= 1; i--)
	{
		int index = -1;
		for (int j = 0; j < this->size; j++)
		{
			if (j == this->START || notIn(j, state))
			{
				continue;
			}
			if (index == -1)index = j;
			int prevDist = this->array[index][state] + matrix[index][lastIndex];
			int newDist = this->array[j][state] + matrix[j][lastIndex];
			if (newDist < prevDist)index = j;
		}
		tour[i] = index;
		state = state ^ (1 << index);
		lastIndex = index;
	}
	tour[0] = this->START;
	tour[this->size] = this->START;
	return tour;
}

//funkcja wywo³ywana w momencie uruchomienia algorytmu
void DynamicProgramming::DP(int** matrix)
{
	this->setup(matrix);
	this->solve(matrix);
	this->minCost = findMinCost(matrix);
	this->tour = findOptimalTour(matrix);
}
//funkcja czyszcz¹ca tablice u¿ywana w destruktorze
void DynamicProgramming::erase()
{
	if (this->array != nullptr)
	{
		for (int i = 0; i < this->size; i++)
		{
			delete[] this->array[i] ;
		}
	}
	if (this->subsets != nullptr)
	{
		delete subsets;
	}
	if (this->tour)
	{
		delete tour;
	}
	this->tour;
	this->subsets = nullptr;
	this->array = nullptr;
}
//funkcja wyœwietlaj¹ca minimaln¹ œcie¿kê oraz koszt tej œcie¿ki
void DynamicProgramming::display()
{
	std::cout << "Sciezka \n";
	for (int i = 0; i < this->size; i++)
	{
		std::cout << this->tour[i] << "->";
	}
	std::cout << this->tour[this->size]<<"\n Dlugosc sciezki"<<this->minCost;

}
//funkcja zwracaj¹ca wskaŸnik na tablicê 
int* DynamicProgramming::returnTour()
{
	return this->tour;
}
//funkcja zwracaj¹ca koszt minimalnej œcie¿ki
int DynamicProgramming::returnMinRoute()
{
	return this->minCost;
}
//funkcja obliczaj¹ca potêgê z liczby
int DynamicProgramming::pow(int val, int pow)
{
	int temp = val;
	if (pow == 0) return 1;
	for (int i = 0; i < pow;i++)
	{
		temp = temp * val;
	}
	return temp;
}
//konstruktor
DynamicProgramming::DynamicProgramming(int** matrix,size_t size)
{
	this->init(size);
}
//destruktor
DynamicProgramming::~DynamicProgramming()
{
	this->erase();
}
