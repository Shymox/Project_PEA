#pragma once
#include <string>
#include "Matrix.h"

class Menu
{
private:
	double time = 0;
	int page=0;
	int index=0;
	bool exit = true;
	const int SIZEX = 6;
	const int SIZEY =3;

	std::string nazwa(int page);
	Matrix* matrix;
	


public:
	void load(std::string name);

	void loop();

	void display();

	void input();

	void writeTime(double time);

	Menu();

	~Menu();
};

