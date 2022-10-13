#include "Cube.h"

void Cube::changeOrientToLeft(int neighbor)
{
	int helper[3][3];
	memmove(helper, faces[neighbor].vertical, sizeof(int) * cubeSize * cubeSize);
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize; j++)
		{
			faces[neighbor].vertical[i][j] = faces[neighbor].horizontal[i][cubeSize - 1 - j];
		}
		memmove(faces[neighbor].horizontal[i], helper[cubeSize - 1 - i], sizeof(int) * cubeSize);
	}
}

void Cube::changeOrientToRight(int neighbor)
{
	int helper[3][3];
	memmove(helper, faces[neighbor].horizontal, sizeof(int) * cubeSize * cubeSize);
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize; j++)
		{
			faces[neighbor].horizontal[i][j] = faces[neighbor].vertical[i][cubeSize - 1 - j];
		}
		memmove(faces[neighbor].vertical[i], helper[cubeSize - 1 - i], sizeof(int) * cubeSize);
	}
}

void Cube::rotateY(int face, int line, string currentNaighbor)
{
	Face currentFace = faces[face];
	int helper[3];

	memmove(helper, faces[face].vertical[line], sizeof(int) * cubeSize);

	for (int i = 0; i < 3; i++)
	{
		memmove(faces[currentFace.index].vertical[line], faces[currentFace.naighbor[currentNaighbor]].vertical[line], sizeof(int) * cubeSize);

		for (int j = 0; j < 3; j++)
		{
			faces[currentFace.index].horizontal[j][line] = faces[currentFace.naighbor[currentNaighbor]].vertical[line][j];
		}
		currentFace = faces[currentFace.naighbor[currentNaighbor]];
	}
	memmove(faces[currentFace.index].vertical[line], helper, sizeof(int) * cubeSize);

	for (int j = 0; j < 3; j++)
	{
		faces[currentFace.index].horizontal[j][line] = helper[j];
	}
}

void Cube::rotateX(int face, int line, string currentNaighbor)
{
	Face currentFace = faces[face];
	int helper[3];

	memmove(helper, faces[face].horizontal[line], sizeof(int) * cubeSize);

	for (int i = 0; i < 3; i++)
	{
		memmove(faces[currentFace.index].horizontal[line], faces[currentFace.naighbor[currentNaighbor]].horizontal[line], sizeof(int) * cubeSize);

		for (int j = 0; j < 3; j++)
		{
			faces[currentFace.index].vertical[j][line] = faces[currentFace.naighbor[currentNaighbor]].horizontal[line][j];
		}
		currentFace = faces[currentFace.naighbor[currentNaighbor]];
	}
	memmove(faces[currentFace.index].horizontal[line], helper, sizeof(int) * cubeSize);

	for (int j = 0; j < 3; j++)
	{
		faces[currentFace.index].vertical[j][line] = helper[j];
	}
}

Cube::Cube(int bars[6][2][3][3])
{
	cubeSize = size(bars[0][0]);

	for (int i = 0; i < 6; i++)
	{
		faces[i] = Face(i, bars[i][0], bars[i][1]);
	}
}

void Cube::print()
{
	//2
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize + 2; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < cubeSize; j++)
		{
			cout << faces[2].horizontal[i][j];
		}
		cout << endl;
	}
	cout << endl;

	//4,3,5,1
	for (int i = 0; i < cubeSize; i++)
	{
		cout << faces[4].horizontal[i][0] << faces[4].horizontal[i][1] << faces[4].horizontal[i][2] << "  ";
		cout << faces[3].horizontal[i][0] << faces[3].horizontal[i][1] << faces[3].horizontal[i][2] << "  ";
		cout << faces[5].horizontal[i][0] << faces[5].horizontal[i][1] << faces[5].horizontal[i][2] << "  ";
		cout << faces[1].horizontal[i][0] << faces[1].horizontal[i][1] << faces[1].horizontal[i][2] << "  ";
		cout << endl;
	}
	cout << endl;

	//0
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize + 2; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < cubeSize; j++)
		{
			cout << faces[0].horizontal[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Cube::rotate(int face, int direction, int line)
{
	Face currentFace = faces[face];
	string currentNaighbor;

	if (direction == 0) //up
	{
		if (line == 0)
		{
			changeOrientToLeft(currentFace.naighbor["leftFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToRight(currentFace.naighbor["rightFace"]);
		}
		rotateY(face, line, "bottomFace");
	}

	if (direction == 1) //down
	{
		if (line == 0)
		{
			changeOrientToRight(currentFace.naighbor["leftFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToLeft(currentFace.naighbor["rightFace"]);
		}
		rotateY(face, line, "topFace");
	}

	if (direction == 2) //left
	{
		if (line == 0)
		{
			changeOrientToRight(currentFace.naighbor["topFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToRight(currentFace.naighbor["bottomFace"]);
		}
		rotateX(face, line, "rightFace");
	}

	if (direction == 3) //right
	{
		if (line == 0)
		{
			changeOrientToLeft(currentFace.naighbor["topFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToLeft(currentFace.naighbor["bottomFace"]);
		}
		rotateX(face, line, "leftFace");
	}
}

bool Cube::check()
{
	for (int i = 0; i < size(faces); i++)
	{
		for (int j = 0; j < cubeSize; j++)
		{
			for (int k = 0; k < cubeSize; k++)
			{
				if (faces[i].horizontal[j][k] != i)
				{
					return false;
				}
			}
		}
	}
	return true;
}
