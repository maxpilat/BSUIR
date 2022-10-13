#include <iostream>
#include "Cube.h"
#include "Face.h"

using namespace std;

int main()
{

	int bars[6][2][3][3] = {
		{{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}},
		{{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}},
		{{{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}, {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}},
		{{{3, 3, 3}, {3, 3, 3}, {3, 3, 3}}, {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}}},
		{{{4, 4, 4}, {4, 4, 4}, {4, 4, 4}}, {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}}},
		{{{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}, {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}}
	};


	
	
	

	/*string path = "test.txt";
	ifstream fin;
	fin.open(path);
	char ch;
	int value;

	while (fin.get(ch))
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int m = 0; m < 3; m++)
					{
						int value = ch - '0';
						bars[i][j][k][m] = value;
						cout << bars[i][j][k][m];
					}
				}
			}
		}
	}
	fin.close();*/


	Cube cube = Cube(bars);

	cube.rotate(0, 3, 2);
	cube.rotate(0, 2, 2);
	
	cube.print();


}
