#include "ReductionMatrixes.h"
#include <iostream>

void ReductionMatrixes::popBack()
{

	int** temp=this->matrix.back();
	this->matrix.pop_back();
	for (size_t i = 0; i < this->size; i++)
	{
		delete[] temp[i];
	}
	delete[] temp;
}
int ReductionMatrixes::countRouteEnd(std::vector<int> path,size_t size)
{
	int count = 0;
	int** temp = this->matrix.front();
	count += temp[0][path[0]];
	for (size_t i = 1; i < path.size(); i++)
	{
		count += temp[path[i - 1]][path[i]];
	}
	count += temp[path[path.size()-1]][0];
	return count;
}
int ReductionMatrixes::countRoute(std::vector<int> path, size_t level)
{
	int count = 0;
	int** temp= this->matrix.front();
	count += temp[0][path[0]];
	for (size_t i = 1; i < level; i++)
	{
		count += temp[i - 1][i];
	}
	if (level = this->size)
	{
		count += temp[path[size]][0];
	}
	return count;
}
int ReductionMatrixes::pushBack()
{
	int** temp = this->matrix.back();
	int** matrixTemp = new int* [size];
	int reduction = 0;
	for (size_t i = 0; i < size; i++)
	{
		matrixTemp[i] = new int[size];
		int min = INT_MAX;
		for (size_t j = 0; j < size; j++)
		{
			matrixTemp[i][j] = temp[i][j];
			if (i != j)
			{
				
				if (min > temp[i][j])
					min = temp[i][j];

			}

			//std::cout << matrixTemp[i][j] << " ";
		}
		//std::cout << "\n";
		for (size_t j = 0; j < size; j++)
		{
			if (i != j)
			{
				matrixTemp[i][j] += -min;
			}
			
			std::cout << matrixTemp[i][j] << " ";
		}
		reduction += min;
	}
	for (size_t i = 0; i < size; i++)
	{
		int min = INT_MAX;
		for (size_t j = 0; j < size; j++)
		{
			if (i != j && min > matrixTemp[j][i])
			{
				min = matrixTemp[j][i];
			}
		}
		for (size_t j = 0; j < size; j++)
		{
			if (i != j)
			{
				matrixTemp[j][i] += -min;
				
			}
			
		}
		reduction += min;
	}
	this->matrix.push_back(matrixTemp);
	return reduction;
}

int ReductionMatrixes::pushBack(int nodeTo,int nodeFrom)
{
	int** temp = this->matrix.back();
	int** matrixTemp = new int* [this->size];
	int reduction = 0;
	for (size_t i = 0; i < size; i++)
	{
		matrixTemp[i] = new int[this->size];
		int min = INT_MAX;
		for (size_t j = 0; j < this->size; j++)
		{
				if (i==j || i==nodeTo || j==nodeFrom || (j==nodeTo && i==nodeFrom))
				{
 					matrixTemp[i][j] = -1;
				}
				else
				{
					matrixTemp[i][j] = temp[i][j];
					if (min > temp[i][j])
					{
						min = temp[i][j];
					}
				}
		}
		for (size_t j = 0; j < this->size; j++)
		{
			if (matrixTemp[i][j] >= 0)
			{
				matrixTemp[i][j] += -min;
			}
		}
		reduction += min;
	}
	for (int i = 0; i <= this->size; i++)
	{
		int min = INT_MAX;
		for (size_t j = 0; j < size; j++)
		{
			if (matrixTemp[j][i]>=0 && min > matrixTemp[j][i])
			{
				min = matrixTemp[j][i];
			}
		}
		for (size_t j = 0; j < size; j++)
		{
			if (matrixTemp[j][i] >= 0)
			{
				matrixTemp[j][i] += -min;

			}

		}
		reduction += min;
	}
	this->matrix.push_back(matrixTemp);

	return reduction;
}

ReductionMatrixes::ReductionMatrixes(int** matrix, size_t size)
{
	int** matrixTemp = new int* [size];
	this->size = size;
	for (size_t i = 0; i < size; i++)
	{
		matrixTemp[i] = new int[size];
		for (size_t j = 0; j < size; j++)
		{
			matrixTemp[i][j] = matrix[i][j];
		}
	}
	this->matrix.push_back(matrixTemp);
}

ReductionMatrixes::~ReductionMatrixes()
{
	while (this->matrix.size() > 0)
	{
		this->popBack();
	}
}
