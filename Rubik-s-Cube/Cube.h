#pragma once

#include "Face.h"

class Cube
{
private:

	int cubeSize;
	Face faces[6];

	void changeOrientToLeft(int neighbor);
	void changeOrientToRight(int neighbor);
	void rotateY(int face, int line, string currentNaighbor);
	void rotateX(int face, int line, string currentNaighbor);

public:

	Cube(int bars[6][2][3][3]);
	void print();
	void rotate(int face, int direction, int line);
	bool check();
};

