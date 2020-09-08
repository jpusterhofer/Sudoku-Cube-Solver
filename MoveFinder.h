#pragma once
#include "Tile.h"

class MoveFinder
{
public:
	MoveFinder();
	MoveFinder(Tile start, Tile end);
	int getMoves();
	
private:
	Tile start;
	Tile end;
	int frontMoves[3][3];
	int topMoves[3][3];
	int bottomMoves[3][3];
	int backMoves[3][3];
	int leftMoves[3][3];
	int rightMoves[3][3];

	void findCornerMoves(int* currTile, int m);
	void findEdgeMoves(int* currTile, int m);

};
