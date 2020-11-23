#pragma once
#include <string>
#include "List.h"
#include "Array.h"
#include "DynamicProgramming.h"

class Matrix
{
private:
	int** matrix;
	size_t size;
	size_t number;
	size_t start;
	int optimum;
	List* answers;
	Array* array;
	Array* sequence;

public:
	void hamiltonCycle();

	int nearestNeighbour(size_t start);

	void bruteForce();

	void displayAnsBF();

	void dynamicProgramming();

	void push(int value, size_t start, size_t end);

	void setOptimum(long optimum);

	int getOptimum();

	void init(size_t size);

	void erase();

	int countPermLeft();

	int getValue(size_t start, size_t end);

	void generatePerm(int size);

	void branchAndBound();

	Matrix reduction(Matrix matrix);

	size_t returnSize();

	void display();

	Matrix();

	~Matrix();

};

