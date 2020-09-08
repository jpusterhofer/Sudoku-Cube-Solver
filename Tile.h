#include <string>
#pragma once
using namespace std;
class Tile
{
public:
	Tile();
	Tile(string face, int r, int c, char dir);

	string getFace();
	int getNum();
	void setNum(int newNum);
	int getID();
	void setID(int newID);
	int getR();
	int getC();
	char getDir();
	bool getIsCorner();

	bool equals(Tile otherTile);
	void changeTile(Tile newTile);

	void rotateTileCW();
	void rotateTileCCW();
	void flipTile();
private:
	string face;
	int num;
	int ID;
	int r;
	int c;
	char dir;
	bool isCorner;
};
