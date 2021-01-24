#include "Matrix.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>
#include "BranchnBound.h"
#include "Timer.h"
#include "SimulatedAnnealing.h"
#include "GeneticAlgorithm.h"

//Funkcja obliczaj¹ca wartoœæ hardcodowanego cyklu hamiltona
void Matrix::hamiltonCycle()
{
	//tablica zawieraj¹ca cykl hamiltona
	int order[6] = { 1,2,3,4,5,6 };
	int start = order[0];
	int cycle = 0;
	for (int i = 1; i < 6; i++)
	{
		cycle += this->matrix[order[i]-1][ order[i - 1]-1];
	}
	std::cout << " Wartosc cyklu Hamiltona:" << cycle<<"\n";
	std::cout << " Optymalny cykl Hamiltona: "<<this->optimum<<"\n";
	if (cycle == this->optimum)
	{
		std::cout << " To jest optymalna sciezka ";
	}
	else
	{
		std::cout << " To nie jest opymalna sciezka ";
	}
}

//Funkcja realizuj¹ca algorytm Najbli¿szego sasiada
int Matrix::nearestNeighbour(size_t start)
{
	Timer* timer = new Timer();
	timer->startCounter();
	int cycle = 0;
	int temp;
	List* list = new List();
	list->pushBack(start);
	//Petla wykonujaca sie dopoki nie przejdziemy przez wszystkie wiezcholki
	while (list->returnSize() < this->size)
	{
		int tmp = INT_MAX;
		int count = 0;
		temp = list->returnLNode();
		//Petla przechodzaca przez wszystkie wierzcholki
		for (int i = 0; i < this->size; i++)
		{
			//Sprawdzamy czy dany wierzcholek nie byl juz wybrany oraz czy odleglosc polaczonej z nim krawedzi jest mniejsza niz poprzedniej najlepszej krawedzi
			if (!list->search(i) && this->matrix[i][temp] < tmp)
			{
				tmp = this->matrix[i][temp];
				count=i;
			}
		}
		//dodajemy wybrany wierzcholek do listy
		list->pushBack(count);
		cycle += (tmp);
	
	}
	//Obliczamy cykl hamiltona
	cycle += matrix[list->returnFNode()][list->returnLNode()];
	//Wyswietlamy liste wiezcholkow
	list->display();
	std::cout << "\n";
	//zwracamy dlugosc cyklu hamiltona
	std::cout << "Czas: " << timer->getCounter();
	return cycle;
}

void Matrix::bruteForce()
{
	Timer *timer = new Timer();
	timer->startCounter();
	generatePerm(this->array->returnSize());
	std::cout << "Czas: " << timer->getCounter();
	std::cout << "\nKONIEC\n";
	this->displayAnsBF();
	
}
void Matrix::displayAnsBF()
{
	for (int i = this->answers->returnSize() - 2; i >=0 ; i--)
	{
		int j = this->answers->returnNode(i);
		std::cout << j << "(" << 100 * static_cast<float>(j) / this->optimum << "%)\n";
	}
	std::cout << "0 ";
	this->sequence->display();
	std::cout << "\n";
}
void Matrix::dynamicProgramming()
{
	Timer* timer = new Timer();
	timer->startCounter();
	DynamicProgramming* DP = new DynamicProgramming(this->matrix,this->size);
	DP->DP(this->matrix);
	std::cout << "Czas: " << timer->getCounter();
	DP->display();
	delete DP;
}

//dodanie krawedzi do macierz
void Matrix::push(int value,size_t start,size_t end)
{
 		this->matrix[end][start] = value;
		this->number++;
}
void Matrix::setOptimum(long optimum)
{
	this->optimum = optimum;
}
int Matrix::getOptimum()
{
	return this->optimum;
}
//inicjalizacja macierzy o podanej liczbie wierzcho³ków
void Matrix::init(size_t size)
{
	this->erase();
	this->sequence = new Array();
	this->array = new Array();
	this->answers = new List();
	this->answers->pushFront(INT_MAX);
	this->size = size;
	for (int i = 1; i < this->size; i++)
	{
		array->pushBack(i);
	}
	this->matrix = new int* [this->size];
	for (size_t i = 0;i < this->size;i++)
	{
		this->matrix[i] = new int[this->size];
		for (size_t j = 0;j < this->size;j++)
		{
			this->matrix[i][j]=0;
		}
	}
}
//wymazanie zawartoœci macierzy
void Matrix::erase()
{
	if (this->matrix != nullptr)
	{
		for (size_t i = 0;i < this->size;i++)
		{
			delete[] this->matrix[i];
		}
		delete[] this->matrix;
	}
	if (this->sequence != nullptr)
	{
		delete this->sequence;
	}
	if (this->array != nullptr)
	{
		delete this->array;
	}
	if (this->answers != nullptr)
	{
		delete this->answers;
	}
	this->sequence = nullptr;
	this->array = nullptr;
	this->answers = nullptr;
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
}


int Matrix::countPermLeft()
{
	int count = 0;
	count += this->matrix[0][this->array->returnValue(0)];
	for (int i = 1; i < this->array->returnSize(); i++)
	{
		count += this->matrix[this->array->returnValue(i-1)][this->array->returnValue(i)];
	}
	count += this->matrix[this->array->returnValue(this->array->returnSize() - 1)][0];
	return count;
}
int Matrix::getValue(size_t start, size_t end)
{
	if (start >= 0 && start < this->size && end >= 0 && end < this->size)
		return this->matrix[end][start];
	return 0;
}
void Matrix::generatePerm(int size)
{
	if (size == 1)
	{
		int j = this->countPermLeft();
		if (j < this->answers->returnFNode())
		{
			this->answers->pushFront(j);
			this->sequence->copy(this->array);
		}
		return;
	}

		for (int i=0;i<size;i++)
		{
			generatePerm(size - 1);
			if (size % 2)
			{
				this->array->fSwap(i, size - 1);
			}
			else
			{
				this->array->fSwap(0, size - 1);
			}
		}
}

void Matrix::branchAndBound()
{
	BranchnBound* branchNbound = new BranchnBound(this->matrix, this->size);
	delete branchNbound;
}

void Matrix::geneticAlgorithm(int period)
{
	GeneticAlgorithm* geneticalgorithm = new GeneticAlgorithm(this->matrix, this->size,this->optimum,period);
}

void Matrix::simulatedAnnealing(int select)
{
	SimulatedAnnealing* simulatedannealing = new SimulatedAnnealing(this->matrix, this->size, this->optimum,select);
}

size_t Matrix::returnSize()
{
	return this->size;
}
//wyœwietlenie zawartoœci macierzy
void Matrix::display()
{
	if (this->matrix!=nullptr)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				std::cout << matrix[j][i] << " ";
			}
			std::cout << "\n";
		}
	}
	std::cout << "Optimum: " << optimum << "\n";
}
//konstruktor Matrix
Matrix::Matrix()
{
	this->sequence = nullptr;
	this->array = nullptr;
	this->answers = nullptr;
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
	this->optimum = INT_MAX;
}
//destruktor Matrix
Matrix::~Matrix()
{
	this->erase();
}
