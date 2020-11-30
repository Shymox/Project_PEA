#include "BranchnBound.h"
#include <iostream>

int BranchnBound::firstLowerBound()
{
	return 0;
}

int BranchnBound::lowerBound()
{
	return 0;
}

int BranchnBound::upperBound()
{
	return 0;
}

int BranchnBound::firstUpperBound(int** matrix)
{
	int count = 0;
	count += matrix[0][1];
	for (int i = 1; i < this->size; i++)
	{
		count += matrix[i - 1][i];
	}
	count += matrix[this->size - 1][0];
	return count;
}

void BranchnBound::permutation(int pathSize, size_t level, size_t prev)
{
	if (level == this->size - 2)
	{
		pathSize += this->reduction->matrix.front()[prev][path[level]] + this->reduction->matrix.front()[path[level]][0];
		if (pathSize < this->upperbound)
		{
			this->upperbound = pathSize;
			this->best_path = this->path;
		}
	}
	else {
		for (size_t i = level; i < this->size - 1; i++)
		{

			//int totalCost = this->reduction->pushBack(this->path[level], this->path[level - 1]) + this->reduction->countRoute(this->path, level);
			//if (totalCost < this->upperbound)
			//{
			size_t tmp = path[level];
			this->path[level] = this->path[i];
			this->path[i] = tmp;

			int temp = pathSize + this->reduction->matrix.front()[prev][this->path[level]];

			int totalCost = pathSize + this->reduction->pushBack(prev, this->path[level]);
			if (totalCost < this->upperbound)
			{
				this->permutation(temp, level + 1, this->path[level]);
			}
			this->reduction->popBack();
			tmp = this->path[level];
			this->path[level] = this->path[i];
			this->path[i] = tmp;
		}
	}
}

void BranchnBound::erase()
{

}

void BranchnBound::init(int** matrix, size_t size)
{
	this->size = size;
	this->upperbound = INT_MAX;
	this->reduction = new ReductionMatrixes(matrix, size);
	for (int i = 1; i < this->size; i++)
	{
		this->path.push_back(i);
	}
	path.size();
	this->permutation(0, 0, 0);
	std::cout << 0 << " ";
	for (int i = 0; i < this->size - 1; i++)
	{
		std::cout << this->best_path[i] << " ";
	}
	std::cout << 0 << '\n';
	std::cout << this->upperbound;
}

BranchnBound::BranchnBound(int** matrix, size_t size)
{
	this->init(matrix, size);
}

BranchnBound::~BranchnBound()
{
}
