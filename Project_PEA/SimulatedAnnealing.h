#pragma once
#include <vector>
#include <list>
#include <vector>
#include <iterator>

class SimulatedAnnealing
{
private:
	int* path,*pathBest;
	size_t size;
	float T, Tmin,variance;
	int costCurrent, cost=0,change,costBest,optimum;
	float beta;
	int maxit = pow(10,5);
	std::list<int> list;
	std::list<int>::iterator id;


public:
	float calculateVariance();

	void init(size_t size, int optimum);

	void firstRandom(int**matrix);

	float propability(int costCurrent, int cost);

	int swap(int** matrix,int indexA, int indexB);

	void newBest();

	void firstTemp();

	float newTemp1();

	float newTemp2();

	float random();

	void loop1(int** matrix, size_t size);

	void loop2(int** matrix, size_t size);

	void display();

	void displayBest();

	SimulatedAnnealing(int** matrix, size_t size, int optimum, int select);

	~SimulatedAnnealing();

};

