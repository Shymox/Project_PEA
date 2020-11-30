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
	count += matrix[this->size][0];
	return 0;
}

void BranchnBound::permutation(int pathSize, size_t level)
{
	if (level == this->size-2)
	{
		pathSize += this->reduction->matrix.front()[level][0];
		if (pathSize<this->upperbound)
		{
			this->upperbound = pathSize;
			this->best_path = this->path;
		}
	}
	else {
		for (size_t i = level; i < this->size; i++)
		{
			
			//int totalCost = this->reduction->pushBack(this->path[level], this->path[level - 1]) + this->reduction->countRoute(this->path, level);
			//if (totalCost < this->upperbound)
			//{
				size_t tmp = path[level];
				this->path[level] = this->path[i];
				this->path[i] = tmp;
				for (int j = 0; j < path.size();j++)
				{
					std::cout << path[j] << " ";
				}
				std::cout <<" "<< level <<" \n";
				
				int temp = pathSize + this->reduction->matrix.front()[this->path[level]][this->path[i]];
				if (true)
				{
					this->permutation(temp, level + 1);
				}
				tmp = this->path[level];
				this->path[level] = this->path[i];
				this->path[i] = tmp;
			//}
			//this->reduction->popBack();
		}
	}
}

void BranchnBound::erase()
{

}

void BranchnBound::init(int** matrix,size_t size)
{
	this->size = size;
	this->reduction = new ReductionMatrixes(matrix, size);
	for(int i=1;i<this->size;i++)
	{
		this->path.push_back(i);
		std::cout << path[i-1]<<' ';
	}
	path.size();
	this->permutation(0,0);
	for (int i = 0; i < this->size; i++)
	{
		std::cout<<this->path[i]<<" ";
	}
	std::cout << '\n';
}

BranchnBound::BranchnBound(int** matrix,size_t size)
{
	this->init(matrix,size);
}

BranchnBound::~BranchnBound()
{
}
