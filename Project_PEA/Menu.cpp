#include "Menu.h"
#include <iostream>
#include <conio.h>


/* 
Klasa Menu zawiera obs³ugê klawiatury oraz menu wraz z wywo³ywaniem wszystkich potrzebnych funkcji z innych klas
*/

std::string Menu::nazwa(int page)
{
	//Etykiety Menu
	switch (page)
	{
	case 0:
		return "Tablica";
		break;
	case 1:
		return "Lista";
		break;
	case 2:
		return "Kopiec";
		break;
	case 3:
		return "BST";
		break;
	}
}
//Pêtla menu
void Menu::loop()
{
	while (exit)
	{
		this->display();
		this->input();
	}

}
//Wyœwietlanie menu
void Menu::display()
{
	std::cout << "========Projekt SDiZO========" << std::endl;
	std::cout << "=========Marzec 2020=========" << std::endl;
	std::cout << "Sterowanie: a-lewo d-prawo w-gora s-dol Wyjscie-Esc" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "<" << nazwa(page)<< ">" << std::endl;



		switch (this->index)
		{
		case 0:
			std::cout << "->" << "Zbuduj z Pliku" << std::endl;
			std::cout << "  " << "Usun" << std::endl;
			std::cout << "  " << "Dodaj" << std::endl;
			std::cout << "  " << "Znajdz" << std::endl;
			std::cout << "  " << "Utworz losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 1:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "->" << "Usun" << std::endl;
			std::cout << "  " << "Dodaj" << std::endl;
			std::cout << "  " << "Znajdz" << std::endl;
			std::cout << "  " << "Utworz losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 2:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Usun" << std::endl;
			std::cout << "->" << "Dodaj" << std::endl;
			std::cout << "  " << "Znajdz" << std::endl;
			std::cout << "  " << "Utworz losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;

		case 3:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Usun" << std::endl;
			std::cout << "  " << "Dodaj" << std::endl;
			std::cout << "->" << "Znajdz" << std::endl;
			std::cout << "  " << "Utworz losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 4:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Usun" << std::endl;
			std::cout << "  " << "Dodaj" << std::endl;
			std::cout << "  " << "Znajdz" << std::endl;
			std::cout << "->" << "Utworz losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 5:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Usun" << std::endl;
			std::cout << "  " << "Dodaj" << std::endl;
			std::cout << "  " << "Znajdz" << std::endl;
			std::cout << "  " << "Utworz losowo" << std::endl;
			std::cout << "->" << "Wyswietl" << std::endl;
			break;
		}


}
//Obs³uga klawiatury
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
				this->timer->startCounter();
				this->array->load(name);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->array->display();
				system("pause");

			}
			break;
			case 1:
				std::cout << "Podaj liczbe do usuniecia:";
				std::cin >> i;
				this->timer->startCounter();
				this->array->popNumber(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->array->display();
				system("pause");
				break;
			case 2:
				size_t j;
				std::cout << "Podaj index do na ktory chcesz dodac:";
				std::cin >> j;
				std::cout << "Podaj wartosc:";
				std::cin >> i;
				this->timer->startCounter();
				this->array->push(i, j);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->array->display();
				system("pause");
				break;
			case 3:
				std::cout << "Podaj liczbe do znalezienia:";
				std::cin >> i;
				this->timer->startCounter();
				if (this->array->search(i))std::cout << "Znaleziono ";
				else std::cout << "Nie znaleziono ";
				this->time = this->timer->getCounter();
				writeTime(this->time);
				//this->array->display();
				system("pause");
				break;
			case 4:
				std::cout << "Podaj wielkosc tablicy:";
				std::cin >> i;
				this->timer->startCounter();
				this->array->random(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->array->display();
				system("pause");
				break;
			case 5:
				this->array->display();
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
				this->timer->startCounter();
				this->list->load(name);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->list->display();
				system("pause");
			}
			break;
			case 1:
				std::cout << "Podaj numer do usuniecia:";
				std::cin >> i;
				this->timer->startCounter();
				this->list->popNumber(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->list->display();
				system("pause");
				break;
			case 2:
			{
				size_t j;
				std::cout << "Podaj index do na ktory chcesz dodac:";
				std::cin >> j;
				std::cout << "Podaj wartosc:";
				std::cin >> i;
				this->timer->startCounter();
				this->list->push(i, j);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->list->display();
				system("pause");
			}
			break;
			case 3:
				std::cout << "Podaj liczbe do znalezienia:";
				std::cin >> i;
				this->timer->startCounter();
				if (this->list->search(i))std::cout << "Znaleziono ";
				else std::cout << "Nie znaleziono ";
				this->time = this->timer->getCounter();
				writeTime(this->time);
				//this->list->display();
				system("pause");
				break;
			case 4:
				std::cout << "Podaj wielkosc listy:";
				std::cin >> i;
				this->timer->startCounter();
				this->list->random(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->list->display();
				system("pause");
				break;
			case 5:
				this->list->display();
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
				this->timer->startCounter();
				this->heap->load(name);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->heap->display("", "", 0);
				system("pause");
			}
			break;
			case 1:
				std::cout << "Podaj numer do usuniecia:";
				std::cin >> i;
				this->timer->startCounter();
				this->heap->pop(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->heap->display("", "", 0);
				system("pause");
				break;
			case 2:
			{

				std::cout << "Podaj wartosc:";
				std::cin >> i;
				this->timer->startCounter();
				this->heap->push(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->heap->display("", "", 0);
				system("pause");
			}
			break;
			case 3:
				std::cout << "Podaj liczbe do znalezienia:";
				std::cin >> i;
				this->timer->startCounter();
				if (this->heap->search(i))std::cout << "Znaleziono";
				else std::cout << "Nie znaleziono";
				this->time = this->timer->getCounter();
				writeTime(this->time);
				//this->heap->display("", "", 0);
				system("pause");
				break;
			case 4:
				std::cout << "Podaj wielkosc kopca:";
				std::cin >> i;
				this->timer->startCounter();
				this->heap->random(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->heap->display("", "", 0);
				system("pause");
				break;
			case 5:
				this->heap->display("", "", 0);
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
				this->timer->startCounter();
				this->tree->load(name);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->tree->display("", "", this->tree->returnRoot());
				system("pause");
			}
			break;
			case 1:
				std::cout << "Podaj numer do usuniecia:";
				std::cin >> i;
				this->timer->startCounter();
				this->tree->pop(this->tree->findNode(i));
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->tree->display("", "", this->tree->returnRoot());
				system("pause");
				break;
			case 2:
			{

				std::cout << "Podaj wartosc:";
				std::cin >> i;
				this->timer->startCounter();
				this->tree->push(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->tree->display("", "", this->tree->returnRoot());
				system("pause");
			}
			break;
			case 3:
				std::cout << "Podaj liczbe do znalezienia:";
				std::cin >> i;
				this->timer->startCounter();
				if (this->tree->search(i))std::cout << "Znaleziono";
				else std::cout << "Nie znaleziono";
				this->time = this->timer->getCounter();
				writeTime(this->time);
				//this->tree->display("", "", this->tree->returnRoot());
				system("pause");
				break;
			case 4:
				std::cout << "Podaj wielkosc kopca:";
				std::cin >> i;
				this->timer->startCounter();
				this->tree->random(i);
				this->time = this->timer->getCounter();
				writeTime(this->time);
				this->tree->display("", "", this->tree->returnRoot());
				system("pause");
				break;
			case 5:
				this->tree->display("", "", this->tree->returnRoot());
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

//Wyœwietla podan¹ wartoœæ czasu
void Menu::writeTime(double time)
{
	std::cout << "Czas operacji wynosil:" << time <<"ms "<<'\n';
	
}

//Inicjalizacja wszystkich u¿ywanych obiektów oraz uruchomienie pêtli
Menu::Menu()
{
	this->array = new Array();
	this->list = new List();
	this->heap = new BinaryHeap();	
	this->tree = new BST();
	this->timer = new Timer();
	this->loop();
}

Menu::~Menu()
{

}
