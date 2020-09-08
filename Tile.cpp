#include "Tile.h"

//Constructors
Tile::Tile()
{
	face = "";
	num = 0;
	ID = 0;
	r = 0;
	c = 0;
	dir = '^';
	isCorner = false;
}

Tile::Tile(string face, int r, int c, char dir)
{
	this->face = face;
	ID = 0;
	this->r = r;
	this->c = c;
	this->dir = dir;
	if ((r == 0 || r == 2) && (c == 0 || c == 2))
	{
		isCorner = true;
	}
	else
	{
		isCorner = false;
	}
}

//Get and set functions
string Tile::getFace()
{
	return face;
}
int Tile::getNum()
{
	return num;
}
void Tile::setNum(int newNum)
{
	num = newNum;
}
int Tile::getID()
{
	return ID;
}
void Tile::setID(int newID)
{
	ID = newID;
}
int Tile::getR()
{
	return r;
}
int Tile::getC()
{
	return c;
}
char Tile::getDir()
{
	return dir;
}
bool Tile::getIsCorner()
{
	return isCorner;
}

//Check if 2 tiles have same ID and are in the same location
bool Tile::equals(Tile otherTile)
{
	if (ID == otherTile.ID && r == otherTile.r && c == otherTile.c && dir == otherTile.dir && face == otherTile.face)
	{
		return true;
	}
	return false;
}

//Update a tile's data except for its location
void Tile::changeTile(Tile newTile)
{
	ID = newTile.ID;
	num = newTile.num;
	dir = newTile.dir;
}
//Change the orientation to match a clockwise rotation
void Tile::rotateTileCW()
{
	switch (dir)
	{
		case '^':
			dir = '>';
			break;
		case '>':
			dir = 'v';
			break;
		case 'v':
			dir = '<';
			break;
		case '<':
			dir = '^';
			break;
	}
}

//Change the orientation to match a counterclockwise rotation
void Tile::rotateTileCCW()
{
	switch (dir)
	{
		case '^':
			dir = '<';
			break;
		case '>':
			dir = '^';
			break;
		case 'v':
			dir = '>';
			break;
		case '<':
			dir = 'v';
			break;
	}
}

//Rotate the orientation of the tile by 180 degrees
void Tile::flipTile()
{
	switch (dir)
	{
		case '^':
			dir = 'v';
			break;
		case '>':
			dir = '<';
			break;
		case 'v':
			dir = '^';
			break;
		case '<':
			dir = '>';
			break;
	}
}
