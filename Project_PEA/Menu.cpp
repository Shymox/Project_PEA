#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <fstream>



/* 
Klasa Menu zawiera obs�ug� klawiatury oraz menu wraz z wywo�ywaniem wszystkich potrzebnych funkcji z innych klas
*/

std::string Menu::nazwa(int page)
{
	//Etykiety Menu
	switch (page)
	{
	case 0:
		return "Zachlanny";
		break;
	case 1:
		return "Brute Force";
		break;
	case 2:
		return "Dynamic Programming";
		break;
	case 3:
		return "B&B";
		break;
	case 4:
		return "Simulated Annealing";
		break;
	case 5:
		return "Genetic Algorithm";
		break;
	case 6:
		return "Ant Colony Optimalisation";
		break;
	}
}
//funkcja �aduje graf z pliku
void Menu::load(std::string name)
{	
	size_t size;
	size_t number;
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data);
		getline(file, data);
		try 
		{
			size = static_cast<size_t>(std::stoi(data));
			matrix->init(size);
		}
		catch (std::exception)
		{
			std::cout << "Blad odczytu: std::exception 2" << '\n';
		}
		for (int i = 0; i < size; i++)
		{
			try
			{
				getline(file, data);
				size_t pos = data.find(' ');
				size_t initialPos = 0;
				int count = 0;
				while (count<size)
				{
					if (initialPos!=pos)
					{
						this->matrix->push(static_cast<int>(std::stoi(data.substr(initialPos, pos - initialPos))), i, count);
						count++;
					}
					initialPos = pos + 1;
					pos = data.find(' ', initialPos);
				}

			}
			catch (std::exception)
			{
				std::cout << "Blad odczytu: std::exception "<<i<< '\n';
			}
		}
		getline(file, data);
		try
		{
			this->matrix->setOptimum(static_cast<long>(std::stoi(data)));
		}
		catch (std::exception)
		{
			std::cout << "Blad odczytu: std::exception 2" << '\n';
		}

		file.close();
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
	system("pause");
}
//P�tla menu
void Menu::loop()
{
	while (exit)
	{
		this->display();
		this->input();
	}

}
//Wy�wietlanie menu
void Menu::display()
{
	std::cout << "========Projekt PEA========" << std::endl;
	std::cout << "=========Pazdziernik 2020=========" << std::endl;
	std::cout << "Sterowanie: a-lewo d-prawo w-gora s-dol Wyjscie-Esc" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "<" << nazwa(page)<< ">" << std::endl;



		switch (this->index)
		{
		case 0:
			std::cout << "->" << "Zbuduj z Pliku" << std::endl;
			std::cout << "  " << "Uruchom algorytm " << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			std::cout << "  " << "Oblicz preprogramowany Cykl Hamiltona" << std::endl;
			break;
		case 1:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "->" << "Uruchom algorytm" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			std::cout << "  " << "Oblicz preprogramowany Cykl Hamiltona" << std::endl;
			break;
		case 2:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Uruchom algorytm" << std::endl;
			std::cout << "->" << "Wyswietl" << std::endl;
			std::cout << "  " << "Oblicz preprogramowany Cykl Hamiltona" << std::endl;
			break;
		case 3:
			std::cout << "  " << "Zbuduj z Pliku" << std::endl;
			std::cout << "  " << "Uruchom algorytm" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			std::cout << "->" << "Oblicz preprogramowany Cykl Hamiltona" << std::endl;
		}


}
//Obs�uga klawiatury
void Menu::input()
{	
	
	char i = _getch();
	switch (i)
	{
	case 'a':
		if (this->page == 0)
		{
			this->page = SIZEX;
		}
		else
		{
			this->page--;
		}
		break;
	case 'd':
		if (this->page == SIZEX)
		{
			this->page = 0;
		}
		else
		{
			this->page++;
		}
		break;
	case 'w':
		if (this->index == 0)
		{
			this->index = SIZEY;
		}
		else
		{
			this->index--;
		}
		break;
	case 's':
		if (this->index == SIZEY)
		{
			this->index = 0;
		}
		else
		{
			this->index++;
		}
		break;
	case 13:
		switch (this->page)
		{

			int i;
		case 0:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				int strt = 0;
				int value;
				std::cout << "Podaj wierzcholek startowy: ";
				std::cin >> strt;
				std::cout << "\n";
				value = this->matrix->nearestNeighbour(strt);
				std::cout << "Dlugosc trasy: " << value << " PRD= " << 100 * value / this->matrix->getOptimum() << "%\n";
				std::cout << "\n";
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;

		case 1:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				std::cout << "\n";
				this->matrix->bruteForce();
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;
		case 2:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				std::cout << "\n";
				this->matrix->dynamicProgramming();
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;
		case 3:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				std::cout << "\n";
				this->matrix->branchAndBound();
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;
		case 4:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				int select;
				std::cout << "Wybierz schemat ch�odzenia \n 0:Liniowy \n 1: Nieliniowy";
				std::cin >> select;
				std::cout << "\n";
				this->matrix->simulatedAnnealing(select);
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;
		case 5:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				//this->load("m12.atsp");
				//std::cout << "m12.atsp;\n";
				//	for (int j = 1; j < 4; j++)
				//	{
				//		std::cout << j * 50 << ";\n";
				//		this->matrix->geneticAlgorithm(5, j * 50);
				//		this->matrix->geneticAlgorithm(15, j * 50);
				//		this->matrix->geneticAlgorithm(30, j * 50);
				//		this->matrix->geneticAlgorithm(45, j * 50);
				//	}
				//this->load("gr17.tsp");
				//for (int j = 1; j < 4; j++)
				//{
				//	std::cout << j * 50 << ";\n";
				//	this->matrix->geneticAlgorithm(5, j * 50);
				//	this->matrix->geneticAlgorithm(15, j * 50);
				//	this->matrix->geneticAlgorithm(30, j * 50);
				//	this->matrix->geneticAlgorithm(45, j * 50);
				//}
				//this->load("ftv33.atsp");
				//for (int j = 1; j < 4; j++)
				//{
				//	std::cout << j * 50 << ";\n";
				//	this->matrix->geneticAlgorithm(5, j * 50);
				//	this->matrix->geneticAlgorithm(15, j * 50);
				//	this->matrix->geneticAlgorithm(30, j * 50);
				//	this->matrix->geneticAlgorithm(45, j * 50);
				//}
				//this->load("ft70.atsp");
				//for (int j = 1; j < 4; j++)
				//{
				//	std::cout << j * 50 << ";\n";
				//	this->matrix->geneticAlgorithm(5, j * 50);
				//	this->matrix->geneticAlgorithm(15, j * 50);
				//	this->matrix->geneticAlgorithm(30, j * 50);
				//	this->matrix->geneticAlgorithm(45, j * 50);
				//}
				//this->load("pr107.tsp");
				//for (int j = 1; j < 4; j++)
				//{
				//	std::cout << j * 50 << ";\n";
				//	this->matrix->geneticAlgorithm(5, j * 50);
				//	this->matrix->geneticAlgorithm(15, j * 50);
				//	this->matrix->geneticAlgorithm(30, j * 50);
				//	this->matrix->geneticAlgorithm(45, j * 50);
				//}
				this->load("pr152.tsp");
				for (int j = 1; j < 4; j++)
				{
					std::cout << j * 50 << ";\n";
					this->matrix->geneticAlgorithm(5, j * 50);
					this->matrix->geneticAlgorithm(15, j * 50);
					this->matrix->geneticAlgorithm(30, j * 50);
					this->matrix->geneticAlgorithm(45, j * 50);
				}
				this->load("gil262.tsp");
				for (int j = 1; j < 4; j++)
				{
					std::cout << j * 50 << ";\n";
					this->matrix->geneticAlgorithm(5, j * 50);
					this->matrix->geneticAlgorithm(15, j * 50);
					this->matrix->geneticAlgorithm(30, j * 50);
					this->matrix->geneticAlgorithm(45, j * 50);
				}
				system("pause");
				system("pause");
				system("pause");
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;

		case 6:
			switch (this->index)
			{
			case 0:
			{
				std::string name;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> name;
				load(name);
			}
			break;
			case 1:
			{
				int temp;
				std::cout << "Podaj Czas dzialania\n";
				std::cin >> temp;
				this->matrix->antAlgorithm(temp, 10, 1, 0.5, 1);
				system("pause");
			}
			break;
			case 2:
				this->matrix->display();
				system("pause");
				break;
			case 3:
				this->load("m6.atsp");
				this->matrix->hamiltonCycle();
				system("pause");
				break;

			}
			break;
		}
		break;
	case 27:
		_exit(0);
		break;
	}
	system("cls");
}

//Wy�wietla podan� warto�� czasu
void Menu::writeTime(double time)
{
	std::cout << "Czas operacji wynosil:" << time <<"ms "<<'\n';
	
}

//Inicjalizacja wszystkich u�ywanych obiekt�w oraz uruchomienie p�tli
Menu::Menu()
{
	this->matrix = new Matrix();
	this->loop();
}

Menu::~Menu()
{

}
