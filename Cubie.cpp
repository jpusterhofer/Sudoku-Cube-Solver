#include "Cubie.h"

//Constructors
Cubie::Cubie()
{
	tile1 = NULL;
	tile2 = NULL;
	tile3 = NULL;
	isCorner = false;
	for (int i = 0; i < 9; i++)
	{
		hasNums[i] = false;
	}
}

Cubie::Cubie(Tile* tile1, Tile* tile2)
{
	this->tile1 = tile1;
	this->tile2 = tile2;
	isCorner = false;
	for (int i = 0; i < 9; i++)
	{
		hasNums[i] = false;
	}
	hasNums[tile1->getNum() - 1] = true;
	hasNums[tile2->getNum() - 1] = true;
}

Cubie::Cubie(Tile* tile1, Tile* tile2, Tile* tile3)
{
	this->tile1 = tile1;
	this->tile2 = tile2;
	this->tile3 = tile3;
	isCorner = true;
	for (int i = 0; i < 9; i++)
	{
		hasNums[i] = false;
	}
	hasNums[tile1->getNum() - 1] = true;
	hasNums[tile2->getNum() - 1] = true;
	hasNums[tile3->getNum() - 1] = true;
}

//Check if the cubie has tiles with certain numbers on them
bool Cubie::containsNums(int num, int num2)
{
	return hasNums[num - 1] && hasNums[num2 - 1];
}

bool Cubie::containsNums(int num, int num2, int num3)
{
	return hasNums[num - 1] && hasNums[num2 - 1] && hasNums[num3 - 1];
}

//Return a pointer to the tile with a certain number on it
Tile* Cubie::find(int num)
{
	if (tile1->getNum() == num)
	{
		return tile1;
	}
	else if (tile2->getNum() == num)
	{
		return tile2;
	}
	else if (isCorner)
	{
		if (tile3->getNum() == num)
		{
			return tile3;
		}
	}
	return NULL;
}