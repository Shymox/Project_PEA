#include "Matrix.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>


void Matrix::hamiltonCycle()
{
	int order[29] = { 24,7,20,8,6,11,1,29,17,28,13,25,12,23,27,21,3,22,26,10,4,15,16,14,9,19,5,2,18 };
	int start = order[0];
	int cycle = 0;
	for (int i = 1; i < 29; i++)
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

int Matrix::nearestNeighbour(size_t start)
{
	int cycle = 0;
	int temp;
	List* list = new List();
	list->pushBack(start);
	
	while (list->returnSize() < this->size)
	{
		int tmp = INT_MAX;
		int count = 0;
		temp = list->returnTail();
		for (int i = 0; i < this->size; i++)
		{
			if (!list->search(i) && this->matrix[i][temp] < tmp)
			{
				tmp = this->matrix[i][temp];
				count=i;
			}
		}
		list->pushBack(count);
		cycle += (tmp);
	}
	cycle += matrix[list->returnFNode()][list->returnTail()];
	list->display();
	std::cout << "\n";
	return cycle;
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
	this->size = size;
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
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
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

	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
	this->optimum = 0;
}
//destruktor Matrix
Matrix::~Matrix()
{
	this->erase();
}
