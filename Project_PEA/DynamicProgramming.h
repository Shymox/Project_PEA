#pragma once
#include "Matrix.h"
#include "Array.h"
class DynamicProgramming
{
private:
	int START = 0;
	int** array;
	int size;
	int minCost;
	int *tour;
	Array* subsets;

public:
	void init(size_t size);

	Array* combinations(int r);

	Array* combinations(int set, int at, int r);

	bool notIn(int i, int subset);

	void setup(int** matrix);

	void solve(int** matrix);

	int findMinCost(int** matrix);

	int* findOptimalTour(int** matrix);

	void DP(int** matrix);

	void erase();

	void display();

	int* returnTour();

	int returnMinRoute();

	int pow(int val, int pow);

	DynamicProgramming(int** matrix,size_t size);

	~DynamicProgramming();
};

