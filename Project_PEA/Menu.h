#pragma once
#include <string>
#include <string>

class Menu
{
private:
	double time = 0;
	int page=0;
	int index=0;
	bool exit = true;
	const int SIZEX = 3;
	const int SIZEY = 5;

	std::string nazwa(int page);


public:
	void loop();

	void display();

	void input();

	void writeTime(double time);

	Menu();

	~Menu();
};

