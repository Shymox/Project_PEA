#pragma once
#include <string>
#include "List.h"

class Matrix
{
private:
	int** matrix;
	size_t size;
	size_t number;
	size_t start;
	int optimum;

public:
	void hamiltonCycle();

	int nearestNeighbour(size_t start);

	void push(int value, size_t start, size_t end);

	void setOptimum(long optimum);

	int getOptimum();

	void init(size_t size);

	void erase();

	void display();

	Matrix();

	~Matrix();

};

