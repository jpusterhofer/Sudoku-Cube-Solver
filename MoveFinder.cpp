#include "MoveFinder.h"
#include <iostream>

//Constructors
MoveFinder::MoveFinder()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frontMoves[i][j] = 9;
			topMoves[i][j] = 9;
			bottomMoves[i][j] = 9;
			backMoves[i][j] = 9;
			leftMoves[i][j] = 9;
			rightMoves[i][j] = 9;
		}
	}
}

MoveFinder::MoveFinder(Tile start, Tile end)
{
	this->start = start;
	this->end = end;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frontMoves[i][j] = 9;
			topMoves[i][j] = 9;
			bottomMoves[i][j] = 9;
			backMoves[i][j] = 9;
			leftMoves[i][j] = 9;
			rightMoves[i][j] = 9;
		}
	}
}

//Calculate how many rotations it would take for a certain tile to reach another tile's location
int MoveFinder::getMoves()
{
	//If the tiles are at the same location, return 0
	if (start.equals(end))
	{
		return 0;
	}

	//If starting tile is a corner, find number of moves to reach other corners
	if (start.getIsCorner())
	{
		if (start.getFace() == "front")
		{
			findCornerMoves(&frontMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "top")
		{
			findCornerMoves(&topMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "bottom")
		{
			findCornerMoves(&bottomMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "back")
		{
			findCornerMoves(&backMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "left")
		{
			findCornerMoves(&leftMoves[start.getR()][start.getC()], 0);
		}
		else
		{
			findCornerMoves(&rightMoves[start.getR()][start.getC()], 0);
		}
		
	}

	//If starting tile is an edge, find number of rotations to reach other edge pieces
	else
	{
		if (start.getFace() == "front")
		{
			findEdgeMoves(&frontMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "top")
		{
			findEdgeMoves(&topMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "bottom")
		{
			findEdgeMoves(&bottomMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "back")
		{
			findEdgeMoves(&backMoves[start.getR()][start.getC()], 0);
		}
		else if (start.getFace() == "left")
		{
			findEdgeMoves(&leftMoves[start.getR()][start.getC()], 0);
		}
		else
		{
			findEdgeMoves(&rightMoves[start.getR()][start.getC()], 0);
		}
	}

	//Return the number of rotations
	if (end.getFace() == "front")
	{
		return frontMoves[end.getR()][end.getC()];
	}
	else if (end.getFace() == "top")
	{
		return topMoves[end.getR()][end.getC()];
	}
	else if (end.getFace() == "bottom")
	{
		return bottomMoves[end.getR()][end.getC()];
	}
	else if (end.getFace() == "back")
	{
		return backMoves[end.getR()][end.getC()];
	}
	else if (end.getFace() == "left")
	{
		return leftMoves[end.getR()][end.getC()];
	}
	else
	{
		return rightMoves[end.getR()][end.getC()];
	}

}

//Recursively find the number of rotations needed to get a corner piece to another corner
void MoveFinder::findCornerMoves(int* currTile, int m)
{
	//If the number of rotations to a spot isn't the minimum, stop
	if (m >= *currTile)
	{
		return;
	}

	//Update the spot with the current min number of rotations
	*currTile = m;

	//Update the locations that are 1 rotation away from the current one
	m++;
	if (currTile == &frontMoves[0][0])
	{
		findCornerMoves(&frontMoves[2][0], m);
		findCornerMoves(&rightMoves[0][0], m);
		findCornerMoves(&topMoves[0][0], m);
	}
	else if (currTile == &frontMoves[0][2])
	{
		findCornerMoves(&frontMoves[0][0], m);
		findCornerMoves(&rightMoves[0][2], m);
		findCornerMoves(&bottomMoves[0][2], m);
	}
	else if (currTile == &frontMoves[2][2])
	{
		findCornerMoves(&frontMoves[0][2], m);
		findCornerMoves(&leftMoves[2][2], m);
		findCornerMoves(&bottomMoves[2][2], m);
	}
	else if (currTile == &frontMoves[2][0])
	{
		findCornerMoves(&frontMoves[2][2], m);
		findCornerMoves(&leftMoves[2][0], m);
		findCornerMoves(&topMoves[2][0], m);
	}
	else if (currTile == &topMoves[0][0])
	{
		findCornerMoves(&topMoves[2][0], m);
		findCornerMoves(&rightMoves[0][2], m);
		findCornerMoves(&backMoves[0][0], m);
	}
	else if (currTile == &topMoves[0][2])
	{
		findCornerMoves(&topMoves[0][0], m);
		findCornerMoves(&rightMoves[2][2], m);
		findCornerMoves(&frontMoves[0][2], m);
	}
	else if (currTile == &topMoves[2][2])
	{
		findCornerMoves(&topMoves[0][2], m);
		findCornerMoves(&leftMoves[0][2], m);
		findCornerMoves(&frontMoves[2][2], m);
	}
	else if (currTile == &topMoves[2][0])
	{
		findCornerMoves(&topMoves[2][2], m);
		findCornerMoves(&leftMoves[2][2], m);
		findCornerMoves(&backMoves[2][0], m);
	}
	else if (currTile == &bottomMoves[0][0])
	{
		findCornerMoves(&bottomMoves[2][0], m);
		findCornerMoves(&frontMoves[0][0], m);
		findCornerMoves(&rightMoves[2][0], m);
	}
	else if (currTile == &bottomMoves[0][2])
	{
		findCornerMoves(&bottomMoves[0][0], m);
		findCornerMoves(&backMoves[0][2], m);
		findCornerMoves(&rightMoves[0][0], m);
	}
	else if (currTile == &bottomMoves[2][2])
	{
		findCornerMoves(&bottomMoves[0][2], m);
		findCornerMoves(&backMoves[2][2], m);
		findCornerMoves(&leftMoves[2][0], m);
	}
	else if (currTile == &bottomMoves[2][0])
	{
		findCornerMoves(&bottomMoves[2][2], m);
		findCornerMoves(&frontMoves[2][0], m);
		findCornerMoves(&leftMoves[0][0], m);
	}
	else if (currTile == &backMoves[0][0])
	{
		findCornerMoves(&backMoves[2][0], m);
		findCornerMoves(&bottomMoves[0][0], m);
		findCornerMoves(&rightMoves[2][2], m);
	}
	else if (currTile == &backMoves[0][2])
	{
		findCornerMoves(&backMoves[0][0], m);
		findCornerMoves(&topMoves[0][2], m);
		findCornerMoves(&rightMoves[2][0], m);
	}
	else if (currTile == &backMoves[2][2])
	{
		findCornerMoves(&backMoves[0][2], m);
		findCornerMoves(&topMoves[2][2], m);
		findCornerMoves(&leftMoves[0][0], m);
	}
	else if (currTile == &backMoves[2][0])
	{
		findCornerMoves(&backMoves[2][2], m);
		findCornerMoves(&bottomMoves[2][0], m);
		findCornerMoves(&leftMoves[0][2], m);
	}
	else if (currTile == &leftMoves[0][0])
	{
		findCornerMoves(&leftMoves[2][0], m);
		findCornerMoves(&frontMoves[0][0], m);
		findCornerMoves(&topMoves[0][2], m);
	}
	else if (currTile == &leftMoves[0][2])
	{
		findCornerMoves(&leftMoves[0][0], m);
		findCornerMoves(&frontMoves[0][2], m);
		findCornerMoves(&bottomMoves[0][0], m);
	}
	else if (currTile == &leftMoves[2][2])
	{
		findCornerMoves(&leftMoves[0][2], m);
		findCornerMoves(&backMoves[0][0], m);
		findCornerMoves(&bottomMoves[0][2], m);
	}
	else if (currTile == &leftMoves[2][0])
	{
		findCornerMoves(&leftMoves[2][2], m);
		findCornerMoves(&backMoves[0][2], m);
		findCornerMoves(&topMoves[0][0], m);
	}
	else if (currTile == &rightMoves[0][0])
	{
		findCornerMoves(&rightMoves[2][0], m);
		findCornerMoves(&topMoves[2][0], m);
		findCornerMoves(&backMoves[2][2], m);
	}
	else if (currTile == &rightMoves[0][2])
	{
		findCornerMoves(&rightMoves[0][0], m);
		findCornerMoves(&bottomMoves[2][2], m);
		findCornerMoves(&backMoves[2][0], m);
	}
	else if (currTile == &rightMoves[2][2])
	{
		findCornerMoves(&rightMoves[0][2], m);
		findCornerMoves(&bottomMoves[2][0], m);
		findCornerMoves(&frontMoves[2][2], m);
	}
	else
	{
		findCornerMoves(&rightMoves[2][2], m);
		findCornerMoves(&topMoves[2][2], m);
		findCornerMoves(&frontMoves[2][0], m);
	}
}

//Recursively find the number of rotation needed for an edge piece to reach another edge piece
void MoveFinder::findEdgeMoves(int* currTile, int m)
{
	if (m >= *currTile)
	{
		return;
	}

	*currTile = m;
	m++;
	if (currTile == &frontMoves[0][1])
	{
		findEdgeMoves(&frontMoves[1][0], m);
		findEdgeMoves(&rightMoves[0][1], m);
	}
	else if (currTile == &frontMoves[1][2])
	{
		findEdgeMoves(&frontMoves[0][1], m);
		findEdgeMoves(&bottomMoves[1][2], m);
	}
	else if (currTile == &frontMoves[2][1])
	{
		findEdgeMoves(&frontMoves[1][2], m);
		findEdgeMoves(&leftMoves[2][1], m);
	}
	else if (currTile == &frontMoves[1][0])
	{
		findEdgeMoves(&frontMoves[2][1], m);
		findEdgeMoves(&topMoves[1][0], m);
	}
	else if (currTile == &topMoves[0][1])
	{
		findEdgeMoves(&topMoves[1][0], m);
		findEdgeMoves(&rightMoves[1][2], m);
	}
	else if (currTile == &topMoves[1][2])
	{
		findEdgeMoves(&topMoves[0][1], m);
		findEdgeMoves(&frontMoves[1][2], m);
	}
	else if (currTile == &topMoves[2][1])
	{
		findEdgeMoves(&topMoves[1][2], m);
		findEdgeMoves(&leftMoves[1][2], m);
	}
	else if (currTile == &topMoves[1][0])
	{
		findEdgeMoves(&topMoves[2][1], m);
		findEdgeMoves(&backMoves[1][0], m);
	}
	else if (currTile == &bottomMoves[0][1])
	{
		findEdgeMoves(&bottomMoves[1][0], m);
		findEdgeMoves(&rightMoves[1][0], m);
	}
	else if (currTile == &bottomMoves[1][2])
	{
		findEdgeMoves(&bottomMoves[0][1], m);
		findEdgeMoves(&backMoves[1][2], m);
	}
	else if (currTile == &bottomMoves[2][1])
	{
		findEdgeMoves(&bottomMoves[1][2], m);
		findEdgeMoves(&leftMoves[1][0], m);
	}
	else if (currTile == &bottomMoves[1][0])
	{
		findEdgeMoves(&bottomMoves[2][1], m);
		findEdgeMoves(&frontMoves[1][0], m);
	}
	else if (currTile == &backMoves[0][1])
	{
		findEdgeMoves(&backMoves[1][0], m);
		findEdgeMoves(&rightMoves[2][1], m);
	}
	else if (currTile == &backMoves[1][2])
	{
		findEdgeMoves(&backMoves[0][1], m);
		findEdgeMoves(&topMoves[1][2], m);
	}
	else if (currTile == &backMoves[2][1])
	{
		findEdgeMoves(&backMoves[1][2], m);
		findEdgeMoves(&leftMoves[0][1], m);
	}
	else if (currTile == &backMoves[1][0])
	{
		findEdgeMoves(&backMoves[2][1], m);
		findEdgeMoves(&bottomMoves[1][0], m);
	}
	else if (currTile == &leftMoves[0][1])
	{
		findEdgeMoves(&leftMoves[1][0], m);
		findEdgeMoves(&frontMoves[0][1], m);
	}
	else if (currTile == &leftMoves[1][2])
	{
		findEdgeMoves(&leftMoves[0][1], m);
		findEdgeMoves(&bottomMoves[0][1], m);
	}
	else if (currTile == &leftMoves[2][1])
	{
		findEdgeMoves(&leftMoves[1][2], m);
		findEdgeMoves(&backMoves[0][1], m);
	}
	else if (currTile == &leftMoves[1][0])
	{
		findEdgeMoves(&leftMoves[2][1], m);
		findEdgeMoves(&topMoves[0][1], m);
	}
	else if (currTile == &rightMoves[0][1])
	{
		findEdgeMoves(&rightMoves[1][0], m);
		findEdgeMoves(&backMoves[2][1], m);
	}
	else if (currTile == &rightMoves[1][2])
	{
		findEdgeMoves(&rightMoves[0][1], m);
		findEdgeMoves(&bottomMoves[2][1], m);
	}
	else if (currTile == &rightMoves[2][1])
	{
		findEdgeMoves(&rightMoves[1][2], m);
		findEdgeMoves(&frontMoves[2][1], m);
	}
	else
	{
		findEdgeMoves(&rightMoves[2][1], m);
		findEdgeMoves(&topMoves[2][1], m);
	}
}
