#include "Steck.h"
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

void Steck::push(int value)
{
	container.push(value);
}

int Steck::pop()
{
	int value = container.top();
	container.pop();
	return value;
}

void Steck::print()
{
	vector <int> copy;

	while (!container.empty())
	{
		copy.push_back(container.top());
		container.pop();
		cout << copy.back() << " ";
	}
	while (!copy.empty())
	{
		container.push(copy.back());
		copy.pop_back();
	}
	cout << endl;
}

void Steck::clear()
{
	while (!container.empty())
	{
		container.pop();
	}
}

int Steck::size()
{
	return container.size();
}
