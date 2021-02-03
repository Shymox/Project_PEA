
#include <vector>
#pragma once



struct ant
{
	int cost;
	std::vector<int>path;
};

class AntAlgorithm
{
	int** matrix;
	float** pheromones;
	int antsNumber;
	ant best;
	std::vector<ant>* ants;
	time_t start;
	size_t size;
	int optimum;
	size_t iteration;
	int period;
	float evaporation;
	float constant;
	bool* visited;
	float beta;
	float alpha;

public:

	void init(int** matrix, size_t size, int optimum, int period, int antsNumber, int startPheromone, float evaporation, float constant);



	double propability(size_t start, size_t end);

	double sum(int start);

	void isBest(ant ant);

	void newIteration();

	void evaporate();

	ant nextAnt();

	void updatePheronome();

	void loop();

	void displayBest();

	AntAlgorithm(int** matrix, size_t size, int optimum, int period, int antsNumber, int startPheromone, float evaporation, float constant);

	~AntAlgorithm();
};

