#pragma once
#include "Matrix.h"
#include <list>
#include "ReductionMatrixes.h"
#include <vector>

class BranchnBound
{
private:
	size_t size;
	std::vector<int> path;
	std::vector<int> best_path;
	int upperbound;
	ReductionMatrixes* reduction;

public:
	int firstLowerBound();

	int lowerBound();

	int upperBound();

	int firstUpperBound(int** matrix);

	void permutation(int pathSize, size_t level, size_t prev);

	void erase();

	void init(int** matrix,size_t size);
	
	BranchnBound(int** matrix,size_t size);

	~BranchnBound();

};

