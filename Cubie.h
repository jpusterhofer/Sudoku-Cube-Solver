#pragma once
#include "Tile.h"
class Cubie
{
public:
	Cubie();
	Cubie(Tile* tile1, Tile* tile2);
	Cubie(Tile* tile1, Tile* tile2, Tile* tile3);
	bool containsNums(int num, int num2);
	bool containsNums(int num, int num2, int num3);
	Tile* find(int num);

private:
	Tile* tile1;
	Tile* tile2;
	Tile* tile3;
	bool isCorner;
	bool hasNums[9];
};