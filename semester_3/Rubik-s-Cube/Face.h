#pragma once

#include <iostream>
#include <map>
using namespace std;

class Face
{
	friend class Cube;

private:

	int index;
	int vertical[3][3];
	int horizontal[3][3];
	map <string, int> naighbor;

	Face();
	Face(int valueIndex, int valueVertical[3][3], int valueHorizontal[3][3]);
};

