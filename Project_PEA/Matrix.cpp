#include "Matrix.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>

//Funkcja obliczaj�ca warto�� hardcodowanego cyklu hamiltona
void Matrix::hamiltonCycle()
{
	//tablica zawieraj�ca cykl hamiltona
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

//Funkcja realizuj�ca algorytm Najbli�szego sasiada
int Matrix::nearestNeighbour(size_t start)
{
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
//inicjalizacja macierzy o podanej liczbie wierzcho�k�w
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
//wymazanie zawarto�ci macierzy
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
//wy�wietlenie zawarto�ci macierzy
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
