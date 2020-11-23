#pragma once
class Array
{
private:
	int* array;
	size_t size;
public:

	void pushFront(int value);

	void pushBack(int value);

	void push(int value, size_t index);

	void popFront();

	void popBack();

	void pop(int index);

	void swap(int indexa, int indexb);

	bool search(int number);

	void write(int index, int value);

	int returnValue(int index);

	void copy(Array* array);

	size_t returnSize();

	void display();

	void erase();

	Array();

	~Array();

};

