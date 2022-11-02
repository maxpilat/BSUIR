#include "Steck.h"
#include "SteckMachine.h"
#include <iostream>
using namespace std;

void factorial(SteckMachine* a, int value);


int main()
{
	SteckMachine a = SteckMachine();
	
	factorial(&a, 7);

	a.print();

}

void factorial(SteckMachine* a, int value)
{
	a->clear();

	if (value == 0 || value == 1)
	{
		a->push(value);
	}
	if (value < 0)
	{
		cout << "error";
	}
	if (value > 1)
	{
		while (value != 0)
		{
			a->push(value--);
			if (a->size() > 1)
			{
				a->mul();
			}
		}
	}

}


