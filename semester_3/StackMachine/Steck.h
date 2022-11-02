#pragma once
#include <stack>
using namespace std;

class Steck
{
protected:
	stack <int> container;
public:
	void push(int value);
	int pop();
	void print();
	void clear();
	int size();
};

