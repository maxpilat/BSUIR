#include "Face.h"

Face::Face()
{
	index = 0;
	naighbor = { {"topFace", 0},
					{"bottomFace", 0},
					{"leftFace", 0},
					{"rightFace", 0}
	};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertical[i][j] = 0;
			horizontal[i][j] = 0;
		}
	}
}

Face::Face(int valueIndex, int valueVertical[3][3], int valueHorizontal[3][3])
{
	index = valueIndex;
	if (index == 0)
	{
		naighbor = { {"topFace", 1},
					 {"bottomFace", 3},
					 {"leftFace", 4},
					 {"rightFace", 5}
		};
	}
	if (index == 1)
	{
		naighbor = { {"topFace", 2},
					 {"bottomFace", 0},
					 {"leftFace", 4},
					 {"rightFace", 5}
		};
	}
	if (index == 2)
	{
		naighbor = { {"topFace", 3},
					 {"bottomFace", 1},
					 {"leftFace", 5},
					 {"rightFace", 4}
		};
	}
	if (index == 3)
	{
		naighbor = { {"topFace", 0},
					 {"bottomFace", 2},
					 {"leftFace", 4},
					 {"rightFace", 5}
		};
	}
	if (index == 4)
	{
		naighbor = { {"topFace", 1},
					 {"bottomFace", 3},
					 {"leftFace", 2},
					 {"rightFace", 0}
		};
	}
	if (index == 5)
	{
		naighbor = { {"topFace", 1},
					 {"bottomFace", 3},
					 {"leftFace", 0},
					 {"rightFace", 2}
		};
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertical[i][j] = valueVertical[i][j];
			horizontal[i][j] = valueHorizontal[i][j];
		}
	}
}
