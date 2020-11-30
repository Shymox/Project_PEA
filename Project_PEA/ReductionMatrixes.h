#pragma once
#include <list>
#include <vector>

class ReductionMatrixes
{


public:
	size_t size;
	std::list<int**> matrix;

	void popBack();

	int countRouteEnd(std::vector<int> path, size_t size);


	int countRoute(std::vector<int> path,size_t level);

	int pushBack();

	int pushBack(int nodeTo,int nodeFrom);

	ReductionMatrixes(int** matrix, size_t size);

	~ReductionMatrixes();
};

